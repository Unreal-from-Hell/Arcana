// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_CanGimmick3.h"

UBTDecorator_CanGimmick3::UBTDecorator_CanGimmick3()
{
	NodeName = TEXT("CanGimmick3");
}

bool UBTDecorator_CanGimmick3::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	bool bResult = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	return false;
}
