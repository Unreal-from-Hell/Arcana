// Fill out your copyright notice in the Description page of Project Settings.


#include "MurdockCharacter.h"

#include "MyAnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"


// Sets default values
AMurdockCharacter::AMurdockCharacter()
{
	PrimaryActorTick.bCanEverTick=true;

	_springArm=CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	_camera=CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

	_springArm->SetupAttachment(GetCapsuleComponent());
	_camera->SetupAttachment(_springArm);

	_springArm->TargetArmLength=800.f;
	
	// 카메라가 회전할 수 있도록 함
	_springArm->bUsePawnControlRotation=true;
	bUseControllerRotationYaw=true;

	GetMesh()->SetRelativeLocationAndRotation(FVector(0.f,0.f,-88.f),
		FRotator(0.f,-90.f,0.f));
	
	static ConstructorHelpers::FObjectFinder<USkeletalMesh>SM(TEXT("SkeletalMesh'/Game/ParagonMurdock/Characters/Heroes/Murdock/Meshes/Murdock.Murdock'"));
	if (SM.Succeeded())
	{
		GetMesh()-> SetSkeletalMesh(SM.Object);
	}
	
	// Character Movement 설정
	GetCharacterMovement()->JumpZVelocity = 550.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 2000.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
}

// Called when the game starts or when spawned
void AMurdockCharacter::BeginPlay()
{
	Super::BeginPlay();

	_animInstance=Cast<UMyAnimInstance>(GetMesh()->GetAnimInstance());
	_animInstance->OnMontageEnded.AddDynamic(this, &AMurdockCharacter::OnAttackMontageEended);
}

//=================================================================================
// 마우스 관련 함수

void AMurdockCharacter::Yaw(float Value)
{
	AddControllerYawInput(Value);
}

void AMurdockCharacter::Pitch(float Value)
{
	AddControllerPitchInput(Value);
}

// ==================================================================================
// 이동 관련 함수

void AMurdockCharacter::MoveForward(float Value)
{
	// controller null check
	if ((Controller != nullptr) && (Value != 0.0f))
		AddMovementInput(GetActorForwardVector(),Value);
	
	_vertical=Value;
}

void AMurdockCharacter::MoveRight(float Value)
{
	if ( (Controller != nullptr) && (Value != 0.0f) )
		AddMovementInput(GetActorRightVector(),Value);
	
	_horizental=Value;
}

void AMurdockCharacter::Sprint()
{
	if(_animInstance->GetWalk())
		return;
	_animInstance->SetSprint(true);
	GetCharacterMovement()->MaxWalkSpeed = 3000.f;
}

void AMurdockCharacter::StopSprint()
{
	if(_animInstance->GetWalk())
		return;
	_animInstance->SetSprint(false);
	GetCharacterMovement()->MaxWalkSpeed = 2000.f;
}

void AMurdockCharacter::Walking()
{
	if(_animInstance->GetSprint())
		return;
	_animInstance->SetWalking(true);
	GetCharacterMovement()->MaxWalkSpeed = 1500.f;
}

void AMurdockCharacter::StopWalking()
{
	if(_animInstance->GetSprint())
		return;
	_animInstance->SetWalking(false);
	GetCharacterMovement()->MaxWalkSpeed = 2000.f;
}

// ==================================================================================
// 공격 관련 함수

void AMurdockCharacter::Attack()
{
	if(_isAttacking)
		return;
	
	_animInstance->PlayAttackMontage();
	_isAttacking=true;
}

void AMurdockCharacter::SKill_1()
{
	if(_isAttacking)
		return;
	
	_animInstance->Skill_1_Montage();
	_isAttacking=true;
}

void AMurdockCharacter::SKill_2()
{
	if(_isAttacking)
		return;

	_animInstance->Skill_2_Montage();
	_isAttacking=true;
}

void AMurdockCharacter::SKill_3()
{
	if(_isAttacking)
		return;
	
	_animInstance->Skill_3_Montage();
	_isAttacking=true;
}

void AMurdockCharacter::SKill_4()
{
	if(_isAttacking)
		return;

	_animInstance->Skill_4_Montage();
	_isAttacking=true;
}

// ==================================================================================
// 몽타주 관련 함수

void AMurdockCharacter::OnAttackMontageEended(UAnimMontage* Montage, bool bInterrupted)
{
	_isAttacking=false;
}

// Called every frame
void AMurdockCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AMurdockCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// check(PlayerInputComponent);

	// 이동 관련 함수 바인딩
	PlayerInputComponent->BindAction("Running", IE_Pressed, this, &AMurdockCharacter::Sprint);
	PlayerInputComponent->BindAction("Running", IE_Released, this, &AMurdockCharacter::StopSprint);
	
	PlayerInputComponent->BindAction("Walking", IE_Pressed, this, &AMurdockCharacter::Walking);
	PlayerInputComponent->BindAction("Walking", IE_Released, this, &AMurdockCharacter::StopWalking);


	// 공격 관련 함수 바인딩
	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &AMurdockCharacter::Attack);
	PlayerInputComponent->BindAction("Skill_1", IE_Pressed, this, &AMurdockCharacter::SKill_1);
	PlayerInputComponent->BindAction("Skill_2", IE_Pressed, this, &AMurdockCharacter::SKill_2);
	PlayerInputComponent->BindAction("Skill_3", IE_Pressed, this, &AMurdockCharacter::SKill_3);
	PlayerInputComponent->BindAction("Skill_4", IE_Pressed, this, &AMurdockCharacter::SKill_4);

}

