// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Sound/SoundCue.h"
#include "Boss1Character.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnAttackEndDelegate);
DECLARE_MULTICAST_DELEGATE(FOnGimmick1EndDelegate);

UCLASS()
class THIRDPERSON_API ABoss1Character : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABoss1Character();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// ==========================================================================================
	// 함수
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void PossessedBy(AController* NewController) override;
	// ==========================================================================================
	// 변수 관련
	float GetHp(){return _hp;};
	void SetHp(float Hp){_hp = Hp;};
	
	bool GetbClearGimmick1(){return _bClearGimmick1;};
	void SetbClearGimmick1(bool bClear){_bClearGimmick1 = bClear;};
	
	bool GetbClearGimmick2(){return _bClearGimmick2;};
	void SetbClearGimmick2(bool bClear){_bClearGimmick2 = bClear;};
	
	bool GetbClearGimmick3(){return _bClearGimmick3;};
	void SetbClearGimmick3(bool bClear){_bClearGimmick3 = bClear;};
	// ===========================================================================================
	// 공격 및 기믹
	
	// 기본 공격
	void Attack();
	FOnAttackEndDelegate OnAttackEnd;

	UFUNCTION()
	void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);
	// 기믹 1
	void Gimmick1();
	FOnGimmick1EndDelegate OnGimmick1End;

	UFUNCTION()
	void OnGimmick1MontageEnded(UAnimMontage* Montage, bool bInterrupted);
	
	// ===========================================================================================
	// 사운드
	void PlayGimmick1Sound();
	void PlayAttackSound();

private:
	UPROPERTY()
	class UBoss1AnimInstance* _animInstance;

	UPROPERTY(VisibleAnywhere)
	bool _isAttacking = false;

	UPROPERTY(VisibleAnywhere)
	float _hp = 100.0f;

	UPROPERTY(VisibleAnywhere)
	bool _bClearGimmick1=false;

	UPROPERTY(VisibleAnywhere)
	bool _bClearGimmick2=false;

	UPROPERTY(VisibleAnywhere)
	bool _bClearGimmick3=false;

	// ============================================================================================
	// 사운드
	UPROPERTY()
	USoundCue* SC_Gimmick1;

	UPROPERTY()
	USoundCue* SC_Attack;
};