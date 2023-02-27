// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_CanGimmick1.generated.h"

/**
 * 
 */
UCLASS()
class THIRDPERSON_API UBTDecorator_CanGimmick1 : public UBTDecorator
{
	GENERATED_BODY()

public:
	UBTDecorator_CanGimmick1();

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
