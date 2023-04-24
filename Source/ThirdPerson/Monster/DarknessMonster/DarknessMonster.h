// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DarknessMonsterAnim.h"
#include "../Monster.h"
#include "DarknessMonster.generated.h"

/**
 * 
 */
UCLASS()
class THIRDPERSON_API ADarknessMonster : public AMonster
{
	GENERATED_BODY()

public:
	ADarknessMonster();

	virtual void BeginPlay() override;

	virtual void Attack() override;

	UFUNCTION()
	void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);

private:
	UPROPERTY()
	UDarknessMonsterAnim* AnimInstance;
	
};
