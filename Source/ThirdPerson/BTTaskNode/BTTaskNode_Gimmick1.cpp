// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskNode_Gimmick1.h"

#include <concrt.h>

#include "AIController.h"
#include "ThirdPerson/Boss1/Boss1Character.h"
#include "ThirdPerson/Boss1/Boss1Controller.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTaskNode_Gimmick1::UBTTaskNode_Gimmick1()
{
	bNotifyTick=true;
	_isGimmick1=false;
}

EBTNodeResult::Type UBTTaskNode_Gimmick1::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	if(OwnerComp.GetBlackboardComponent()->GetValueAsBool(ABoss1Controller::Gimmick1)==false)
		return EBTNodeResult::Failed;
	
	ABoss1Character* Boss1Character = Cast<ABoss1Character>(OwnerComp.GetAIOwner()->GetPawn());
	if(Boss1Character == nullptr)
		return EBTNodeResult::Failed;

	Boss1Character->Gimmick1();
	_isGimmick1 = true;
	
	Boss1Character->OnGimmick1End.AddLambda([this]()->void
	{
		_isGimmick1=false;
	});
	
	// TODO 기믹 추가로 구현
	// 1. 오브젝트 떨어지는 것
	// 2. safezone 구현
	// 3. 이펙트, 사운드 구현

	OwnerComp.GetBlackboardComponent()->SetValueAsBool(ABoss1Controller::Gimmick1, false);
	// 일단 Inprogress에 머물게 한다. 공격이 끝나기 전까지 계속 지연 시켜준다
	return EBTNodeResult::InProgress;
}

void UBTTaskNode_Gimmick1::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	if(!_isGimmick1)
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
}

