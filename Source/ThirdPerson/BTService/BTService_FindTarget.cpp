// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_FindTarget.h"

#include "AIController.h"
#include "ThirdPerson/Boss1/Boss1Controller.h"
#include "ThirdPerson/MurdockCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

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
	float DetectRadius = 800.0f;

	TSubclassOf<AMurdockCharacter> ClassToFind;
	ClassToFind = AMurdockCharacter::StaticClass();
	TArray<AActor*> FoundCharacter;
	UGameplayStatics::GetAllActorsOfClass(World, ClassToFind, FoundCharacter);

	for(auto Enemy : FoundCharacter)
	{
		AMurdockCharacter* Murdock = Cast<AMurdockCharacter>(Enemy);
		FVector BossLocation = ControllingPawn->GetActorLocation();
		FVector CharacterLocation = Murdock->GetActorLocation();

		FVector Distance = BossLocation-CharacterLocation;
		if(Distance.Length() < DetectRadius)
		{
			OwnerComp.GetBlackboardComponent()->SetValueAsObject(ABoss1Controller::TargetKey, Murdock);
			DrawDebugSphere(World, BossLocation, DetectRadius, 16, FColor::Green, false, 0.2f);
			
			DrawDebugPoint(World, Murdock->GetActorLocation(), 10.0f, FColor::Blue, false, 0.2f);
			DrawDebugLine(World, ControllingPawn->GetActorLocation(), Murdock->GetActorLocation(), FColor::Blue, false, 0.27f);
		}
		else
		{
			OwnerComp.GetBlackboardComponent()->SetValueAsObject(ABoss1Controller::TargetKey, nullptr);
			OwnerComp.GetAIOwner()->StopMovement();
			// TODO 원래 위치로 되돌아가서 정찰하기
			DrawDebugSphere(World, BossLocation, DetectRadius, 16, FColor::Red, false, 0.2f);
		}
	}
}
