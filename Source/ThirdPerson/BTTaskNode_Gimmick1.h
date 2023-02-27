// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskNode_Gimmick1.generated.h"

/**
 * 
 */
UCLASS()
class THIRDPERSON_API UBTTaskNode_Gimmick1 : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTaskNode_Gimmick1();

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:
	bool _isAttacking = false;
};
