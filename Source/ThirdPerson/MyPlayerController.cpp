// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"

#include "BehaviorTree/BehaviorTreeTypes.h"
#include "GameFramework/SpringArmComponent.h"


AMyPlayerController::AMyPlayerController()
{
}

void AMyPlayerController::Yaw(float Value)
{
	if(_pawn && Value != 0.0f)
	{
		FRotator rot = _pawn->GetControlRotation();
		_pawn->AddControllerYawInput(Value);
	}
}

void AMyPlayerController::Pitch(float Value)
{
	if(_pawn && Value != 0.0f)
	{
		FRotator rot = _pawn->GetControlRotation();
		_pawn->AddControllerPitchInput(Value);
	}
}

void AMyPlayerController::MoveForward(float Value)
{
	// Pawn null check
	if (_pawn && Value != 0.0f)
	{
		// TODO 
		// 카메라가 바라보는 방향을 기준으로 해야함
		FRotator rot = GetControlRotation();
		FVector dir = FRotationMatrix(rot).GetScaledAxis(EAxis::X);
		
		_pawn->AddMovementInput(dir, Value);
	}

	_MurdockCharacter->_vertical=Value;
}

void AMyPlayerController::MoveRight(float Value)
{
	// Pawn null check
	if (_pawn && Value != 0.0f)
	{
		// TODO 
		// 카메라가 바라보는 방향을 기준으로 해야함
		FRotator rot = GetControlRotation();
		FVector dir = FRotationMatrix(rot).GetScaledAxis(EAxis::Y);
		
		_pawn->AddMovementInput(dir, Value);
	}

	_MurdockCharacter->_horizental=Value;
}

void AMyPlayerController::Jump()
{
	GetCharacter()->Jump();
}

void AMyPlayerController::StopJumping()
{
	GetCharacter()->StopJumping();
}


void AMyPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// 움직임
	InputComponent->BindAxis("Move Forward / Backward", this, &AMyPlayerController::MoveForward);
	InputComponent->BindAxis("Move Right / Left", this, &AMyPlayerController::MoveRight);
	// 마우스
	InputComponent->BindAxis("Turn Right / Left Mouse", this, &AMyPlayerController::Yaw);
	InputComponent->BindAxis("Look Up / Down Mouse", this, &AMyPlayerController::Pitch);

	// 점프
	InputComponent->BindAction("Jump", IE_Pressed, this, &AMyPlayerController::Jump);
	InputComponent->BindAction("Jump", IE_Released, this, &AMyPlayerController::StopJumping);

	// InputComponent->BindAction("Running", IE_Pressed, this, &AMyPlayerController::Sprint);
	// InputComponent->BindAction("Running", IE_Released, this, &AMyPlayerController::StopSprint);
	//
	// InputComponent->BindAction("Walking", IE_Pressed, this, &AMyPlayerController::Walking);
	// InputComponent->BindAction("Walking", IE_Released, this, &AMyPlayerController::StopWalking);
	//
	// //공격 관련 함수 바인딩
	// InputComponent->BindAction("Attack", IE_Pressed, this, &AMyPlayerController::Attack);
	// InputComponent->BindAction("Skill_1", IE_Pressed, this, &AMyPlayerController::SKill_1);
	// InputComponent->BindAction("Skill_2", IE_Pressed, this, &AMyPlayerController::SKill_2);
	// InputComponent->BindAction("Skill_3", IE_Pressed, this, &AMyPlayerController::SKill_3);
	// InputComponent->BindAction("Skill_4", IE_Pressed, this, &AMyPlayerController::SKill_4);
	
	
}

void AMyPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	_pawn=GetPawn();
	_MurdockCharacter=Cast<AMurdockCharacter>(GetCharacter());
}
