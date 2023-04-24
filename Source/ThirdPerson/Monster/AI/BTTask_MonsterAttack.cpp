// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_MonsterAttack.h"

#include "AIController.h"
#include "../Monster.h"

UBTTask_MonsterAttack::UBTTask_MonsterAttack()
{
	bNotifyTick=true;
	isAttacking=false;
}

EBTNodeResult::Type UBTTask_MonsterAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	AMonster* Monster = Cast<AMonster>(OwnerComp.GetAIOwner()->GetPawn());
	if(Monster == nullptr)
		return EBTNodeResult::Failed;

	Monster->Attack();
	isAttacking=true;
	
	Monster->OnAttackEnd.AddLambda([this]()->void
	{
		isAttacking=false;
	});
	
	return EBTNodeResult::InProgress;
}

void UBTTask_MonsterAttack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	if(!isAttacking)
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
}
