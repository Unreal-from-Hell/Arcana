// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CountessAnimInstance.generated.h"

UCLASS()
class THIRDPERSON_API UCountessAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UCountessAnimInstance();
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	//몬티지 갖고오기
	void PlayAttackMontage() {Montage_Play(AttackMontage,1.f);};
	void PlayParringMontage() {Montage_Play(Parring,1.f);};
	//Skill R 애니메이션 갖고와서 실행 
	void PlaySkillSequence(){Montage_Play(SkillAnimationR,1.f);}
	void PlaySkillF(){Montage_Play(SkillAnimationF,1.f);}
	void PlaySkillQ(){Montage_Play(SkillAnimationQ,1.f);}
	void PlaySkillE(){Montage_Play(SkillAnimationE,1.f);}
	void PlaySkillT(){Montage_Play(SkillAnimationT,1.f);}
	void JumpToSection(int32 SectionIndex);
	void JumpToSectionQ(int32 SectionIndex);
	void JumpToSectionE(int32 SectionIndex);

	FName GetAttackMontageName(int32 SectionIndex);

	void ChangeAttacked();
private:
	UFUNCTION()
	//void AnimNotify_AttackHit(); // AttackHit 마다 소리 예정 
	void AnimNotify();
	
private:
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category=Pawn, meta=(AllowPrivateAccess=true))
	float Speed;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category=Pawn, meta=(AllowPrivateAccess=true))
	bool IsFalling;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category=Pawn, meta=(AllowPrivateAccess=true))
	bool Attacked; // 블루프린트에서 모션을 위해 사용 델리게이트로 대체할 예정 
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category=Pawn, meta=(AllowPrivateAccess=true))
	UAnimMontage* AttackMontage;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category=Pawn, meta=(AllowPrivateAccess=true))
	UAnimMontage* Parring;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category=Pawn, meta=(AllowPrivateAccess=true))
	UAnimMontage* SkillAnimationR;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category=Pawn, meta=(AllowPrivateAccess=true))
	UAnimMontage* SkillAnimationF;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category=Pawn, meta=(AllowPrivateAccess=true))
	UAnimMontage* SkillAnimationQ;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category=Pawn, meta=(AllowPrivateAccess=true))
	UAnimMontage* SkillAnimationE;
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category=Pawn, meta=(AllowPrivateAccess=true))
	UAnimMontage* SkillAnimationT;
};
