// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterAnimInstance.h"

UMonsterAnimInstance::UMonsterAnimInstance()
{
}

void UMonsterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	APawn* Pawn = TryGetPawnOwner();
	if(IsValid(Pawn))
	{
		Speed=Pawn->GetVelocity().Size();
		
	}
}

void UMonsterAnimInstance::PlayAttackMontagee()
{
	if(!AttackMontage)
		return;
	
	Montage_Play(AttackMontage, 1.f);
}

void UMonsterAnimInstance::JumpToSection()
{
	if(!AttackMontage)
		return;;
	
	int32 randomindex = FMath::RandRange(0,1);
	FName name = FName(*FString::Printf(TEXT("Attack%d"), randomindex));
	Montage_JumpToSection(name, AttackMontage);
	
}
