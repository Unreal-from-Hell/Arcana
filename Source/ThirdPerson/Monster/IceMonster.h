// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IceMonsterAnim.h"
#include "Monster.h"
#include "ThirdPerson/Boss1/Boss1Character.h"
#include "IceMonster.generated.h"

/**
 * 
 */
UCLASS()
class THIRDPERSON_API AIceMonster : public AMonster
{
	GENERATED_BODY()

public:
	AIceMonster();

	virtual void BeginPlay() override;

	void Attack();
	FOnAttackEndDelegate OnAttackEnd;

	UFUNCTION()
	void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);

private:
	UIceMonsterAnim* AnimInstance;
};
