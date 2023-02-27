// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_CanGimmick1.h"

#include "AIController.h"
#include "Boss1Character.h"
#include "Boss1Controller.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTDecorator_CanGimmick1::UBTDecorator_CanGimmick1()
{
	NodeName = TEXT("CanGimmick1");
}

bool UBTDecorator_CanGimmick1::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	bool bResult = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);
	
	ABoss1Character* Boss1 = Cast<ABoss1Character>(OwnerComp.GetAIOwner()->GetPawn());
	float Hp = Boss1->GetHp();
	
	if(Boss1 == nullptr)
		return false;
	
	if(Hp == 75.0f)
	{
		Boss1->SetHp(74.99f);
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(ABoss1Controller::Gimmick1, true);
		bResult = true;
	}
	else
	{
		bResult = false;
	}
	
	return bResult;
}
