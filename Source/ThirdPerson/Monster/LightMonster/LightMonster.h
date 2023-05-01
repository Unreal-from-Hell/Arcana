// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Monster.h"
//#include "ThirdPerson/LightMonsterAnim.h"
#include "LightMonster.generated.h"

/**
 * 
 */
UCLASS()
class THIRDPERSON_API ALightMonster : public AMonster
{
	GENERATED_BODY()

public:
	ALightMonster();
	virtual void BeginPlay() override;
	virtual void Attack() override;

	UFUNCTION()
	void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);

private:
	//UPROPERTY()
	//ULightMonsterAnim* AnimInstance;
};
