// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterAIController.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BlackboardData.h"

const FName AMonsterAIController::TargetKey(TEXT("Target"));

AMonsterAIController::AMonsterAIController()
{
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BT(TEXT("BehaviorTree'/Game/ThirdPerson/Blueprints/Monster/ElementalMonster/AI/BT_Monster.BT_Monster'"));
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BB(TEXT("BlackboardData'/Game/ThirdPerson/Blueprints/Monster/ElementalMonster/AI/BB_Monster.BB_Monster'"));

	if(BB.Succeeded())
		BBAsset=BB.Object;

	if(BT.Succeeded())
		BTAsset=BT.Object;
}

void AMonsterAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	UBlackboardComponent* BlackboardComponent = Blackboard.Get();
	this->Blackboard=BlackboardComponent;

	if(UseBlackboard(BBAsset, BlackboardComponent))
	{
		RunBehaviorTree(BTAsset);
	}
}

void AMonsterAIController::StopAI()
{
	UBehaviorTreeComponent* BehaviorTreeComponent=Cast<UBehaviorTreeComponent>(BrainComponent);
	if(BehaviorTreeComponent==nullptr)
		return;

	BehaviorTreeComponent->StopTree(EBTStopMode::Safe);
}
