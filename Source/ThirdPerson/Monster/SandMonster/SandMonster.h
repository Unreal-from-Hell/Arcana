// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SandMonsterAnim.h"
#include "../Monster.h"
#include "SandMonster.generated.h"

/**
 * 
 */
UCLASS()
class THIRDPERSON_API ASandMonster : public AMonster
{
	GENERATED_BODY()

public:
	ASandMonster();
	virtual void BeginPlay() override;
	virtual void Attack() override;

	UFUNCTION()
	void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);
private:
	UPROPERTY()
	USandMonsterAnim* AnimInstance;
};
