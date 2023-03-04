// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_FindPatrolPos.h"

#include "AIController.h"
#include "ThirdPerson/boss1/Boss1Controller.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"

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

	// TODO
	// HomePos 값이 제대로 안채워져서 이상한 값이 Origin에 저장됨
	// HomePos 기준으로 정찰하도록 변경하기
	FVector Origin=OwnerComp.GetBlackboardComponent()->GetValueAsVector(ABoss1Controller::HomePosKey);
	FNavLocation NextPatrol;
	
	if(NavSystem->GetRandomPointInNavigableRadius(FVector::ZeroVector, 500.0f, NextPatrol))
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(ABoss1Controller::PatrolPosKey, NextPatrol.Location);
		return EBTNodeResult::Succeeded;
	}

	UE_LOG(LogTemp, Warning, TEXT("Nav Failed !"));
	return EBTNodeResult::Failed;
}
