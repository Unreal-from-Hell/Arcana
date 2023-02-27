// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAnimInstance.h"

#include "MurdockCharacter.h"
#include "GameFramework/Character.h"
#include "GameFramework/PawnMovementComponent.h"

UMyAnimInstance::UMyAnimInstance()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage> Attack(TEXT("AnimMontage'/Game/ThirdPerson/Blueprints/Anim/Fire_Reload.Fire_Reload'"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage> Skill_1(TEXT("AnimMontage'/Game/ThirdPerson/Blueprints/Anim/Skill_Q.Skill_Q'"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage> Skill_2(TEXT("AnimMontage'/Game/ThirdPerson/Blueprints/Anim/Skill_W.Skill_W'"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage> Skill_3(TEXT("AnimMontage'/Game/ThirdPerson/Blueprints/Anim/Skill_E.Skill_E'"));
	static ConstructorHelpers::FObjectFinder<UAnimMontage> Skill_4(TEXT("AnimMontage'/Game/ThirdPerson/Blueprints/Anim/Skill_R.Skill_R'"));
	if(Attack.Succeeded() && Skill_1.Succeeded() && Skill_2.Succeeded() && Skill_3.Succeeded() && Skill_4.Succeeded())
	{
		_attackMontage=Attack.Object;
		_SKill_1_Montage=Skill_1.Object;
		_SKill_2_Montage=Skill_2.Object;
		_SKill_3_Montage=Skill_3.Object;
		_SKill_4_Montage=Skill_4.Object;
	}
}

void UMyAnimInstance::PlayAttackMontage()
{
	Montage_Play(_attackMontage,1.f);
}

void UMyAnimInstance::Skill_1_Montage()
{
	Montage_Play(_SKill_1_Montage, 1.f);
}

void UMyAnimInstance::Skill_2_Montage()
{
	Montage_Play(_SKill_2_Montage, 1.f);
}

void UMyAnimInstance::Skill_3_Montage()
{
	Montage_Play(_SKill_3_Montage, 1.f);
}

void UMyAnimInstance::Skill_4_Montage()
{
	Montage_Play(_SKill_4_Montage, 1.f);
}

void UMyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	// 매 틱마다 폰에 접근해서 정보를 가져옴 
	Super::NativeUpdateAnimation(DeltaSeconds);

	auto pawn = TryGetPawnOwner();
	if(IsValid(pawn))
	{
		_speed=pawn->GetVelocity().Size();

		auto Character = Cast<AMurdockCharacter>(pawn);
		if(Character)
		{
			_isFalling=Character->GetMovementComponent()->IsFalling();
			_vertical=Character->_vertical;
			_horizental=Character->_horizental;
		}
	}
}

void UMyAnimInstance::AnimNotify_Fire()
{
	
}
