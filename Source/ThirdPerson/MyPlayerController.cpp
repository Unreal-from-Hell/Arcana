// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"

#include "BehaviorTree/BehaviorTreeTypes.h"
#include "Character/MyCharacter.h"
#include "GameFramework/SpringArmComponent.h"


AMyPlayerController::AMyPlayerController()
{
}


void AMyPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	MyPawn = Cast<AMyCharacter>(GetPawn());
}
void AMyPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
}


void AMyPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
}


