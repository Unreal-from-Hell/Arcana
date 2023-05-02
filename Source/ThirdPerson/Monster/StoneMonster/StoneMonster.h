// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StoneMonsterAnim.h"
#include "../Monster.h"
#include "StoneMonster.generated.h"

/**
 * 
 */
UCLASS()
class THIRDPERSON_API AStoneMonster : public AMonster
{
	GENERATED_BODY()
public:
	AStoneMonster();
	virtual void BeginPlay() override;
	virtual void Attack() override;

	UFUNCTION()
	void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);
private:
	UPROPERTY()
	UStoneMonsterAnim* AnimInstance;
};
