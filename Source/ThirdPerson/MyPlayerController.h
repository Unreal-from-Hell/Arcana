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
	// 마우스 관련 함수
	// ========================================
	void Yaw(float Value);
	void Pitch(float Value);
	// 움직임 관련 함수
	// ========================================
	// 걷기
	void MoveForward(float Value);
	void MoveRight(float Value);
	// 점프
	void Jump();
	void StopJumping();
	// // 달리기
	// void Sprint();
	// void StopSprint();
	// // 천천히 걷기
	// void Walking();
	// void StopWalking();
	// // 공격 관련 함수
	// // ========================================
	// // 기본 공격
	// void Attack();
	//
	// // 스킬 공격
	// void SKill_1();
	// void SKill_2();
	// void SKill_3();
	// void SKill_4();

	// ===========================================
	// 초기화 관련 함수
	virtual void SetupInputComponent() override;
	virtual void OnPossess(APawn* InPawn) override;

private:
	APawn* _pawn;
	AMurdockCharacter* _MurdockCharacter;

};


