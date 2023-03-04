// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_CanGimmick1.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "ThirdPerson/Boss1/Boss1Character.h"
#include "ThirdPerson/Boss1/Boss1Controller.h"

class ABoss1Character;

UBTDecorator_CanGimmick1::UBTDecorator_CanGimmick1()
{
	NodeName = TEXT("CanGimmick1");
}

bool UBTDecorator_CanGimmick1::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	bool bResult = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);
	
	ABoss1Character* Boss1 = Cast<ABoss1Character>(OwnerComp.GetAIOwner()->GetPawn());
	if(Boss1 == nullptr)
		return false;
	
	bool bClearGimmick1 = Boss1->GetbClearGimmick1();
	
	if(bClearGimmick1)
		return false;
	
	float Hp = Boss1->GetHp();
	
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
