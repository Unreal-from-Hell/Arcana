// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_CanGimmick1.h"

#include <string>

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
	
	if(Hp <= 75.1f)
	{
		// 체력이 기믹1의 조건을 만족했다면 하던 것을 멈추고 기믹1 수행
		UE_LOG(LogTemp, Warning, TEXT("hp: %f"), Hp);
		Boss1->SetHp(75.0f);
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(ABoss1Controller::Gimmick1, true);
		bResult = true;
	}
	else
	{
		bResult = false;
	}
	
	return bResult;
}
