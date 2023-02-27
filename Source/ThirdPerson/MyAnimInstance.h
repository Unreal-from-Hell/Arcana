// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MyAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class THIRDPERSON_API UMyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	// 생성자
	// 애니메이션 몽타주 등을 초기화하는 작업
	UMyAnimInstance();

	// 공격 몽타주 관련
	void PlayAttackMontage();
	void Skill_1_Montage();
	void Skill_2_Montage();
	void Skill_3_Montage();
	void Skill_4_Montage();

	// 변수 관련 함수
	bool GetSprint(){return _isSprint;};
	void SetSprint(bool isSprint){_isSprint=isSprint;};

	bool GetWalk(){return _isWalking;};
	void SetWalking(bool isWalking){_isWalking=isWalking;};

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

private:
	UFUNCTION()
	void AnimNotify_Fire();
	
private:
	// ==================================================================================
	// 상태 관련 변수
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, meta=(AllowPrivateAccess=true))
	float _speed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, meta=(AllowPrivateAccess=true))
	bool _isFalling;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, meta=(AllowPrivateAccess=true))
	bool _isSprint=false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, meta=(AllowPrivateAccess=true))
	bool _isWalking=false;

	// 블렌드 스페이스 관련 변수
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, meta=(AllowPrivateAccess=true))
	float _horizental;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, meta=(AllowPrivateAccess=true))
	float _vertical;

	// ==================================================================================
	// 몽타주
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, meta=(AllowPrivateAccess=true))
	UAnimMontage* _attackMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, meta=(AllowPrivateAccess=true))
	UAnimMontage* _SKill_1_Montage;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, meta=(AllowPrivateAccess=true))
	UAnimMontage* _SKill_2_Montage;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, meta=(AllowPrivateAccess=true))
	UAnimMontage* _SKill_3_Montage;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, meta=(AllowPrivateAccess=true))
	UAnimMontage* _SKill_4_Montage;
};
