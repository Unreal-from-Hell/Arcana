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
	static ConstructorHelpers::FObjectFinder<UParticleSystem> Shield(TEXT("ParticleSystem'/Game/ThirdPerson/Blueprints/Monster/Boss1/Particles/FX/P_Boss1_Shield.P_Boss1_Shield'"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> Drop(TEXT("ParticleSystem'/Game/ThirdPerson/Blueprints/Monster/Boss1/Particles/FX/P_DropBoss1.P_DropBoss1'"));
	
	if(Gimmick1.Succeeded())
		SC_Gimmick1 = Gimmick1.Object;
	
	if(Attack.Succeeded())
		SC_Attack = Attack.Object;

	if(Shield.Succeeded())
		_shieldParticle = Shield.Object;

	if(Drop.Succeeded())
		_dropBoss1Particle = Drop.Object;
	
	bUseControllerRotationYaw=false;
	GetCharacterMovement()->bUseControllerDesiredRotation=false;
	GetCharacterMovement()->bOrientRotationToMovement=true;
	GetCharacterMovement()->RotationRate=FRotator(0.0f,480.0f,0.0f);
}

// Called when the game starts or when spawned
void ABoss1Character::BeginPlay()
{
	Super::BeginPlay();

	_gimmick1Location = GetActorLocation();
	_isAttacking=false;
	_animInstance=Cast<UBoss1AnimInstance>(GetMesh()->GetAnimInstance());
	_animInstance->OnMontageEnded.AddDynamic(this, &ABoss1Character::OnAttackMontageEnded);
	_animInstance->OnMontageEnded.AddDynamic(this, &ABoss1Character::OnGimmick1MontageEnded);
}

// Called every frame
void ABoss1Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 임시로 체력이 계속 줄도록 
	if(GetHp()>75.01f)
		SetHp(GetHp()-0.1f);
	
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
	SpawnGimmick1ShieldParticle();
}

void ABoss1Character::OnGimmick1MontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	// 기믹1 사전동작 끝
	// TODO 기믹1 함수 호출 후 기믹1 진행
	
	// TODO 기믹1을 통과했을 때 호출
	OnGimmick1End.Broadcast();
	SetbClearGimmick1(true);
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

void ABoss1Character::SpawnGimmick1ShieldParticle()
{
	// 임시로 Particle 생성
	for(auto TargetPoint : TargetPoints)
	{
		FVector SpawnFrontLocation = TargetPoint->GetActorLocation() + FVector(0,0,100); 
		FVector SpawnLeftLocation =  SpawnFrontLocation + FVector(100, -100, 0);
		FVector SpawnRightLocation = SpawnFrontLocation + FVector(100, 100, 0);
		FVector SpawnBehindLocation = SpawnFrontLocation + FVector(200, 0, 0);
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), _shieldParticle, SpawnFrontLocation, FRotator::ZeroRotator, true);
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), _shieldParticle, SpawnLeftLocation, FRotator(0,90,0), true);
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), _shieldParticle, SpawnRightLocation, FRotator(0,90,0), true);
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), _shieldParticle, SpawnBehindLocation, FRotator::ZeroRotator, true);
	}
		
}

void ABoss1Character::SpawnGimmick1DropParticle()
{
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), _dropBoss1Particle, GetActorLocation(), FRotator::ZeroRotator, true);
}

