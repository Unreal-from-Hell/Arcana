// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Sound/SoundCue.h"
#include "Boss1AnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class THIRDPERSON_API UBoss1AnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UBoss1AnimInstance();

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	// =======================================================================================
	// 애니메이션 실행
	void PlayAttackMontage();
	void PlayGimmick1AfterMontage();
	void JumpToSection();
	void PlayGimmick1Montage();

private:
	// =======================================================================================
	// 애니메이션 노티파이
	UFUNCTION()
	void AnimNotify_AttackHit();

	UFUNCTION()
	void AnimNotify_Gimmick1();

	UFUNCTION()
	void AnimNotify_ShieldHit();

	UFUNCTION()
	void AnimNotify_PlayDropBoss1Particle();
private:
	// ========================================================================================
	// 상태 관련 변수
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, meta=(AllowPrivateAccess=true))
	float _speed;

	// =======================================================================================
	// 몽타주
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, meta=(AllowPrivateAccess=true))
	UAnimMontage* _attackMontage;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, meta=(AllowPrivateAccess=true))
	UAnimMontage* _gimmick1Montage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, meta=(AllowPrivateAccess=true))
	UAnimMontage* _gimmick2Montage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, meta=(AllowPrivateAccess=true))
	UAnimMontage* _gimmick1AfterMontage;
};
