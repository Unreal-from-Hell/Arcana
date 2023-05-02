// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SpaceMonsterAnim.h"
#include "../Monster.h"
#include "SpaceMonster.generated.h"

/**
 * 
 */
UCLASS()
class THIRDPERSON_API ASpaceMonster : public AMonster
{
	GENERATED_BODY()
public:
	ASpaceMonster();
	virtual void BeginPlay() override;
	virtual void Attack() override;

	UFUNCTION()
	void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);
private:
	UPROPERTY()
	USpaceMonsterAnim* AnimInstance;
};
