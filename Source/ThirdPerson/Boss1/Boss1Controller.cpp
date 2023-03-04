// Fill out your copyright notice in the Description page of Project Settings.


#include "Boss1Controller.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BlackboardData.h"

const FName ABoss1Controller::HomePosKey(TEXT("HomePos"));
const FName ABoss1Controller::PatrolPosKey(TEXT("PatrolPos"));
const FName ABoss1Controller::TargetKey(TEXT("Target"));
const FName ABoss1Controller::Gimmick1(TEXT("Gimmick1"));
const FName ABoss1Controller::Gimmick2(TEXT("Gimmick2"));
const FName ABoss1Controller::Gimmick3(TEXT("Gimmick3"));

ABoss1Controller::ABoss1Controller()
{
	static ConstructorHelpers::FObjectFinder<UBlackboardData>BB(TEXT("BlackboardData'/Game/ThirdPerson/Blueprints/Monster/Boss1/BB_Boss1.BB_Boss1'"));
	if(BB.Succeeded())
	{
		_BBAsset=BB.Object;  
	}
	static ConstructorHelpers::FObjectFinder<UBehaviorTree>BT(TEXT("BehaviorTree'/Game/ThirdPerson/Blueprints/Monster/Boss1/BT_Boss1.BT_Boss1'"));
	if(BT.Succeeded())
	{
		_BTAsset=BT.Object;
	}
	
}

void ABoss1Controller::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	UBlackboardComponent* BlackboardComp = Blackboard.Get();
	this->Blackboard=BlackboardComp;
	
	if(UseBlackboard(_BBAsset, BlackboardComp))
	{
		// TODO HomePos 값이 제대로 안채워져서 수정필요
		BlackboardComp->SetValueAsVector(HomePosKey, InPawn->GetActorLocation());
		BlackboardComp->SetValueAsBool(Gimmick1, false);
		BlackboardComp->SetValueAsBool(Gimmick2, false);
		BlackboardComp->SetValueAsBool(Gimmick3, false);
		RunBehaviorTree(_BTAsset);		
	}
}

void ABoss1Controller::StopAI()
{
	UBehaviorTreeComponent* BehaviorTreeComponent=Cast<UBehaviorTreeComponent>(BrainComponent);
	if(BehaviorTreeComponent==nullptr)
		return;

	BehaviorTreeComponent->StopTree(EBTStopMode::Safe);
}
