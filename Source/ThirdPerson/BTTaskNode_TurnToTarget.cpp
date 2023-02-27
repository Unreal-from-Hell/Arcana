// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskNode_TurnToTarget.h"

#include "AIController.h"
#include "Boss1Character.h"
#include "Boss1Controller.h"
#include "MurdockCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTaskNode_TurnToTarget::UBTTaskNode_TurnToTarget()
{
	NodeName = TEXT("TurnToTarget");
}

EBTNodeResult::Type UBTTaskNode_TurnToTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	ABoss1Character* Boss1 = Cast<ABoss1Character>(OwnerComp.GetAIOwner()->GetPawn());
	if(Boss1 == nullptr)
		return EBTNodeResult::Failed;

	AMurdockCharacter* Target = Cast<AMurdockCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(ABoss1Controller::TargetKey));
	if(Target == nullptr)
		return EBTNodeResult::Failed;
	
	// 타겟으로의 방향벡터 구하기
	FVector LockVector = Target->GetActorLocation() - Boss1->GetActorLocation();
	LockVector.Z = 0.0f;
	// 방향벡터로부터 각도를 구한다 (내적 이용)
	FRotator TargetRot = FRotationMatrix::MakeFromX(LockVector).Rotator();
	// 각도만큼 2초에 걸쳐서 회전 시킨다
	Boss1->SetActorRotation(FMath::RInterpTo(Boss1->GetActorRotation(), TargetRot, GetWorld()->GetDeltaSeconds(), 2.0f));

	return EBTNodeResult::Succeeded;
}
