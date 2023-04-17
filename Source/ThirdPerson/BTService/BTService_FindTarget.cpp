// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_FindTarget.h"

#include "AIController.h"
#include "ThirdPerson/Boss1/Boss1Controller.h"
#include "ThirdPerson/MurdockCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "ThirdPerson/Character/MyCharacter.h"
#include "ThirdPerson/Monster/MonsterAIController.h"

UBTService_FindTarget::UBTService_FindTarget()
{
	NodeName = TEXT("FindTarget");
	
	Interval = 1.0f;
	RandomDeviation = 0;
}

void UBTService_FindTarget::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (nullptr == ControllingPawn) return;

	UWorld* World = ControllingPawn->GetWorld();
	float DetectRadius = 2000.0f;

	TSubclassOf<AMyCharacter> ClassToFind;
	ClassToFind = AMyCharacter::StaticClass();
	TArray<AActor*> FoundCharacter;
	UGameplayStatics::GetAllActorsOfClass(World, ClassToFind, FoundCharacter);

	for(auto Enemy : FoundCharacter)
	{
		AMyCharacter* Character = Cast<AMyCharacter>(Enemy);
		FVector BossLocation = ControllingPawn->GetActorLocation();
		FVector CharacterLocation = Character->GetActorLocation();

		FVector Distance = BossLocation-CharacterLocation;
		if(Distance.Length() < DetectRadius)
		{
			OwnerComp.GetAIOwner()->StopMovement();
			OwnerComp.GetBlackboardComponent()->SetValueAsObject("Target", Character);
			
			DrawDebugSphere(World, BossLocation, DetectRadius, 16, FColor::Green, false, 0.2f);
			DrawDebugPoint(World, Character->GetActorLocation(), 10.0f, FColor::Blue, false, 0.2f);
			DrawDebugLine(World, ControllingPawn->GetActorLocation(), Character->GetActorLocation(), FColor::Blue, false, 0.27f);
		}
		else
		{
			// TODO StopMovement 개선이 필요함
			OwnerComp.GetAIOwner()->StopMovement();
			OwnerComp.GetBlackboardComponent()->SetValueAsObject(ABoss1Controller::TargetKey, nullptr);
			DrawDebugSphere(World, BossLocation, DetectRadius, 16, FColor::Red, false, 0.2f);
		}
	}
}
