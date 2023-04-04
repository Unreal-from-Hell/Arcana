// Fill out your copyright notice in the Description page of Project Settings.



#include "CountessAnimInstance.h"
#include "MyCharacter.h"
#include "GameFramework/Character.h"
#include "GameFramework/PawnMovementComponent.h"
//생성자에서 몽티지 불러옴 
UCountessAnimInstance::UCountessAnimInstance()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage>AM(TEXT("AnimMontage'/Game/ThirdPerson/Blueprints/Character/Animation/Montage/S_Countess_Skeleton_Montage.S_Countess_Skeleton_Montage'"));
	if(AM.Succeeded())
	{
		AttackMontage = AM.Object;
	}
	static ConstructorHelpers::FObjectFinder<UAnimMontage>PR(TEXT("AnimMontage'/Game/ThirdPerson/Blueprints/Character/Animation/Montage/RightClick'"));
	if(PR.Succeeded())
	{
		Parring = PR.Object;
	}
	static ConstructorHelpers::FObjectFinder<UAnimMontage>SkillAni(TEXT("AnimMontage'/Game/ThirdPerson/Blueprints/Character/Animation/Montage/SMM_Dash'"));
	if(SkillAni.Succeeded())
	{
		SkillAnimationR = SkillAni.Object;
	}
	static ConstructorHelpers::FObjectFinder<UAnimMontage>SkillQ(TEXT("AnimMontage'/Game/ThirdPerson/Blueprints/Character/Animation/Montage/SMM_Q'"));
	if(SkillQ.Succeeded())
	{
		SkillAnimationQ = SkillQ.Object;
	}
	static ConstructorHelpers::FObjectFinder<UAnimMontage>SkillE(TEXT("AnimMontage'/Game/ThirdPerson/Blueprints/Character/Animation/Montage/SMM_E'"));
	if(SkillE.Succeeded())
	{
		SkillAnimationE = SkillE.Object;
	}
	static ConstructorHelpers::FObjectFinder<UAnimMontage>SkillF(TEXT("AnimMontage'/Game/ThirdPerson/Blueprints/Character/Animation/Montage/SM_F'"));
	if(SkillF.Succeeded())
	{
		SkillAnimationF = SkillF.Object;
	}
	static ConstructorHelpers::FObjectFinder<UAnimMontage>SkillT(TEXT("AnimMontage'/Game/ThirdPerson/Blueprints/Character/Animation/Montage/SMM_T'"));
	if(SkillT.Succeeded())
	{
		SkillAnimationT = SkillT.Object;
		
	}
}

// 실시간 애니인스턴스에 캐릭터상태 업데이트 
void UCountessAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	auto Pawn = TryGetPawnOwner();
	if(IsValid(Pawn))
	{
		Speed = Pawn->GetVelocity().Size();

		auto Character = Cast<ACharacter>(Pawn);
		if (Character)
		{
			IsFalling = Character->GetMovementComponent()->IsFalling();
		}
	}
}


// 각 스킬 캐릭터 섹션 저장
void UCountessAnimInstance::JumpToSection(int32 SectionIndex)
{
	FName Name = GetAttackMontageName(SectionIndex);
	Montage_JumpToSection(Name,AttackMontage);
}
void UCountessAnimInstance::JumpToSectionQ(int32 SectionIndex)
{
	FName Name = GetAttackMontageName(SectionIndex);
	Montage_JumpToSection(Name,SkillAnimationQ);
}
void UCountessAnimInstance::JumpToSectionE(int32 SectionIndex)
{
	FName Name = GetAttackMontageName(SectionIndex);
	Montage_JumpToSection(Name,SkillAnimationE);
}

FName UCountessAnimInstance::GetAttackMontageName(int32 SectionIndex)
{
	return FName(*FString::Printf(TEXT("Attack%d"),SectionIndex));
}

void UCountessAnimInstance::ChangeAttacked()
{
	if (Attacked == true)
		Attacked = false;
	else
		Attacked = true;
}

//타이밍에 맞는 함수 호출예정 
void UCountessAnimInstance::AnimNotify()
{
	
}
