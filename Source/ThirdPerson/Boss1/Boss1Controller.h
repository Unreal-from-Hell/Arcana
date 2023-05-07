// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Boss1Controller.generated.h"

/**
 * 
 */
UCLASS()
class THIRDPERSON_API ABoss1Controller : public AAIController
{
	GENERATED_BODY()

public:
	ABoss1Controller();
	virtual void OnPossess(APawn* InPawn) override;

	void RunAI();
	// AI를 종료시키는 함수
	void StopAI();

	// BlackBoard Data Key
	static const FName HomePosKey;
	static const FName PatrolPosKey;
	static const FName TargetKey;
	static const FName Gimmick1;
	static const FName Gimmick2;
	static const FName Gimmick3;
 
private:
	UPROPERTY()
	UBehaviorTree* _BTAsset;

	UPROPERTY()
	UBlackboardData* _BBAsset;
};
