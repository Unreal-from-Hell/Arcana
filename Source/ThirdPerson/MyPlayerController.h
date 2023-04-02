// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MurdockCharacter.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class THIRDPERSON_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AMyPlayerController();

protected:
	/** True if the controlled character should navigate to the mouse cursor. */
	uint32 bMoveToMouseCursor : 1;

	virtual void OnPossess(APawn* InPawn) override;
	// Begin PlayerController interface
	UFUNCTION()
	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;
	// End PlayerController interface

	/** Input handlers for SetDestination action. */
	void OnSetDestinationPressed();
	void OnSetDestinationReleased();


private:
	bool bInputPressed; // Input is bring pressed
	bool bIsTouch; // Is it a touch device
	float FollowTime; // For how long it has been pressed
	class AMyCharacter* MyPawn = nullptr;

};


