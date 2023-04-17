// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskNode_TurnToTarget.h"
#include "AIController.h"
#include "ThirdPerson/Boss1/Boss1Character.h"
#include "ThirdPerson/Boss1/Boss1Controller.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "ThirdPerson/Character/MyCharacter.h"

UBTTaskNode_TurnToTarget::UBTTaskNode_TurnToTarget()
{
	NodeName = TEXT("TurnToTarget");
}

EBTNodeResult::Type UBTTaskNode_TurnToTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if(ControllingPawn == nullptr)
		return EBTNodeResult::Failed;

	AMyCharacter* Target = Cast<AMyCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject("Target"));
	if(Target == nullptr)
		return EBTNodeResult::Failed;
	
	// 타겟으로의 방향벡터 구하기
	FVector LockVector = Target->GetActorLocation() - ControllingPawn->GetActorLocation();
	LockVector.Z = 0.0f;
	// 방향벡터로부터 각도를 구한다 (내적 이용)
	FRotator TargetRot = FRotationMatrix::MakeFromX(LockVector).Rotator();
	// 각도만큼 2초에 걸쳐서 회전 시킨다
	ControllingPawn->SetActorRotation(FMath::RInterpTo(ControllingPawn->GetActorRotation(), TargetRot, GetWorld()->GetDeltaSeconds(), 2.0f));

	return EBTNodeResult::Succeeded;
}
