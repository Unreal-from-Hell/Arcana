// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WaterMonsterAnim.h"
#include "../Monster.h"
#include "WaterMonster.generated.h"

/**
 * 
 */
UCLASS()
class THIRDPERSON_API AWaterMonster : public AMonster
{
	GENERATED_BODY()
public:
	AWaterMonster();
	virtual void BeginPlay() override;
	virtual void Attack() override;

	UFUNCTION()
	void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);
private:
	UWaterMonsterAnim* AnimInstance;
};
