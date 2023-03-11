// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_CanGimmick2.h"


UBTDecorator_CanGimmick2::UBTDecorator_CanGimmick2()
{
	NodeName = TEXT("CanGimmick2");
}

bool UBTDecorator_CanGimmick2::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	bool bResult = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	return false;
}
