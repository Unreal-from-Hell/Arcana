// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_FindPatrolPos.h"

#include "AIController.h"
#include "ThirdPerson/boss1/Boss1Controller.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BTCompositeNode.h"

UBTTask_FindPatrolPos::UBTTask_FindPatrolPos()
{
	NodeName=TEXT("FindPatrolPos");
}

EBTNodeResult::Type UBTTask_FindPatrolPos::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);
	
	APawn* ControllingPawn=OwnerComp.GetAIOwner()->GetPawn();
	if(ControllingPawn == nullptr)
		return EBTNodeResult::Failed;
	
	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(ControllingPawn->GetWorld());
	if(NavSystem == nullptr)
		return EBTNodeResult::Failed;
	
	FVector Origin=OwnerComp.GetBlackboardComponent()->GetValueAsVector(ABoss1Controller::HomePosKey);
	FNavLocation NextPatrol;
	
	if(NavSystem->GetRandomPointInNavigableRadius(Origin, 1000.0f, NextPatrol))
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(ABoss1Controller::PatrolPosKey, NextPatrol.Location);
		return EBTNodeResult::Succeeded;
	}

	UE_LOG(LogTemp, Warning, TEXT("Nav Failed !"));
	return EBTNodeResult::Failed;
}
