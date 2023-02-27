// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskNode_Attack.h"

#include "AIController.h"
#include "Boss1Character.h"
#include "MurdockCharacter.h"

UBTTaskNode_Attack::UBTTaskNode_Attack()
{
	bNotifyTick=true;
	_isAttacking=false;
}

EBTNodeResult::Type UBTTaskNode_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);
	
	ABoss1Character* Boss1Character = Cast<ABoss1Character>(OwnerComp.GetAIOwner()->GetPawn());
	if(Boss1Character == nullptr)
		return EBTNodeResult::Failed;

	Boss1Character->Attack();
	_isAttacking = true;
	// 해당 람다식이 AttackEnd Delegate를 호출하면 IsAttacking을 false로 
	Boss1Character->OnAttackEnd.AddLambda([this]()->void
	{
		_isAttacking=false;
	});
	
	// 일단 Inprogress에 머물게 한다. 공격이 끝나기 전까지 계속 지연 시켜준다
	return EBTNodeResult::InProgress;
}

// 매 틱마다 공격이 끝났는지를 확인
void UBTTaskNode_Attack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	if(!_isAttacking)
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
}
