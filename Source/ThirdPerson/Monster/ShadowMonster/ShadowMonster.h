// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ShadowMonsterAnim.h"
#include "../Monster.h"
#include "ShadowMonster.generated.h"

/**
 * 
 */
UCLASS()
class THIRDPERSON_API AShadowMonster : public AMonster
{
	GENERATED_BODY()

public:
	AShadowMonster();
	virtual void BeginPlay() override;
	virtual void Attack() override;

	UFUNCTION()
	void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);
private:
	UPROPERTY()
	UShadowMonsterAnim* AnimInstance;
};
