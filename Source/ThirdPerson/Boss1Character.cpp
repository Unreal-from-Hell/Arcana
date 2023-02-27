// Fill out your copyright notice in the Description page of Project Settings.


#include "Boss1Character.h"

#include "Boss1AnimInstance.h"
#include "Components/AudioComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABoss1Character::ABoss1Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	static ConstructorHelpers::FObjectFinder<USoundCue> Gimmick1(TEXT("SoundCue'/Game/ThirdPerson/Blueprints/Monster/Boss1/Sound/Cue/Boss1_Gimmick1_Cue.Boss1_Gimmick1_Cue'"));;
	static ConstructorHelpers::FObjectFinder<USoundCue> Attack(TEXT("SoundCue'/Game/ThirdPerson/Blueprints/Monster/Boss1/Sound/Cue/Boss1_Attack.Boss1_Attack'"));;
	
	if(Gimmick1.Succeeded())
		SC_Gimmick1 = Gimmick1.Object;
	
	if(Attack.Succeeded())
		SC_Attack = Attack.Object;
	
	bUseControllerRotationYaw=false;
	GetCharacterMovement()->bUseControllerDesiredRotation=false;
	GetCharacterMovement()->bOrientRotationToMovement=true;
	GetCharacterMovement()->RotationRate=FRotator(0.0f,480.0f,0.0f);
}

// Called when the game starts or when spawned
void ABoss1Character::BeginPlay()
{
	Super::BeginPlay();

	_isAttacking=false;
	_animInstance=Cast<UBoss1AnimInstance>(GetMesh()->GetAnimInstance());
	_animInstance->OnMontageEnded.AddDynamic(this, &ABoss1Character::OnAttackMontageEnded);
	_animInstance->OnMontageEnded.AddDynamic(this, &ABoss1Character::OnGimmick1MontageEnded);
}

// Called every frame
void ABoss1Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABoss1Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABoss1Character::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	if(IsPlayerControlled())
	{
		// TODO 플레이어가 컨트롤중일 때
	}
	else
	{
		GetCharacterMovement()->MaxWalkSpeed=400.0f;
	}
}

void ABoss1Character::Attack()
{
	if(_isAttacking)
		return;
	
	_animInstance->PlayAttackMontage();
	_animInstance->JumpToSection();
	PlayAttackSound();
	_isAttacking=true;
}

void ABoss1Character::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	_isAttacking=false;
	OnAttackEnd.Broadcast();
}

void ABoss1Character::Gimmick1()
{
	_animInstance->PlayGimmick1Montage();
	PlayGimmick1Sound();
}

void ABoss1Character::OnGimmick1MontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	OnGimmick1End.Broadcast();
}

void ABoss1Character::PlayGimmick1Sound()
{
	if(SC_Gimmick1 != nullptr)
		UGameplayStatics::PlaySoundAtLocation(this, SC_Gimmick1, GetActorLocation());
}

void ABoss1Character::PlayAttackSound()
{
	if(SC_Attack != nullptr)
		UGameplayStatics::PlaySoundAtLocation(this, SC_Attack, GetActorLocation());
}

