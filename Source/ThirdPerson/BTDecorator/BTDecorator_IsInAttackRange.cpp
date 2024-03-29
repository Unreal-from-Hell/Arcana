// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_IsInAttackRange.h"

#include "AIController.h"
#include "ThirdPerson/MurdockCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "ThirdPerson/Boss1/Boss1Controller.h"
#include "ThirdPerson/Character/MyCharacter.h"

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

	AMyCharacter* Target = Cast<AMyCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(ABoss1Controller::TargetKey));
	if(Target == nullptr)
		return false;

	bResult = (Target->GetDistanceTo(ControllingPawn)) <= 500.0f;
	return bResult;
}
