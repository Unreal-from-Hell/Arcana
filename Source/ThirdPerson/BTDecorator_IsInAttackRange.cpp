// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_IsInAttackRange.h"

#include "AIController.h"
#include "Boss1Controller.h"
#include "MurdockCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTDecorator_IsInAttackRange::UBTDecorator_IsInAttackRange()
{
	NodeName = TEXT("CanAttack");
}

bool UBTDecorator_IsInAttackRange::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp,
                                                              uint8* NodeMemory) const
{
	bool bResult = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if(ControllingPawn == nullptr)
		return false;

	AMurdockCharacter* Target = Cast<AMurdockCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(ABoss1Controller::TargetKey));
	if(Target == nullptr)
		return false;

	bResult = (Target->GetDistanceTo(ControllingPawn)) <= 200.0f;
	return bResult;
}
