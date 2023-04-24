// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_MonsterAttack.generated.h"

/**
 * 
 */
UCLASS()
class THIRDPERSON_API UBTTask_MonsterAttack : public UBTTaskNode
{
	GENERATED_BODY()

	UBTTask_MonsterAttack();

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:
	bool isAttacking = false;
	
};
