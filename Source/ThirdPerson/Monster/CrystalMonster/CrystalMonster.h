// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CrystalMonsterAnim.h"
#include "../Monster.h"
#include "CrystalMonster.generated.h"

/**
 * 
 */
UCLASS()
class THIRDPERSON_API ACrystalMonster : public AMonster
{
	GENERATED_BODY()

public:
	ACrystalMonster();

	virtual void BeginPlay() override;

	virtual void Attack() override;

	UFUNCTION()
	void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);

private:
	UPROPERTY()
	UCrystalMonsterAnim* AnimInstance;
};
