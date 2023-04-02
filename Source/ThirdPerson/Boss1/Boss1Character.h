// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TargetPoint.h"
#include "GameFramework/Character.h"
#include "Sound/SoundCue.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
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

	FVector GetGimmick1Location(){return _gimmick1Location;};
	
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
	void Gimmick1DropProjectile();
	FOnGimmick1EndDelegate OnGimmick1End;

	UFUNCTION()
	void OnGimmick1MontageEnded(UAnimMontage* Montage, bool bInterrupted);

	// 기믹1 투사체
	UFUNCTION()
	void Drop();
	
	// ===========================================================================================
	// 사운드
	void PlayGimmick1Sound();
	void PlayAttackSound();
	void PlaySwordSound();

	// ===========================================================================================
	// 이펙트
	void SpawnGimmick1ShieldParticle();
	void SpawnBoss1DropParticle();
	
public:
	// ===========================================================================================
	// 변수
	// Gimmick1 안전구역 Target Point 배열
	UPROPERTY(EditAnywhere, Category = "Target Points")
	TArray<ATargetPoint*> TargetPoints;

private:
	// ===========================================================================================
	// 변수
	UPROPERTY()
	class UBoss1AnimInstance* _animInstance;

	UPROPERTY(VisibleAnywhere)
	bool _isAttacking = false;

	UPROPERTY(VisibleAnywhere)
	float _hp = 100.0f;

	UPROPERTY(VisibleAnywhere)
	float _maxHp = 100.0f;

	UPROPERTY(VisibleAnywhere)
	FVector _gimmick1Location;

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

	UPROPERTY()
	USoundCue* SC_Sword;

	// ============================================================================================
	// 이펙트
	UPROPERTY(EditAnywhere, Category="Effects")
	UParticleSystem* P_NotSafeZoneParticle;

	UPROPERTY(EditAnywhere, Category="Effects")
	UParticleSystem* P_SafeZoneParticle;

	UPROPERTY(EditAnywhere, Category="Effects")
	UParticleSystem* P_DropBoss1Particle;

	// Target Point에 추가한 particle의 배열
	UPROPERTY(VisibleAnywhere)
	TArray<UParticleSystemComponent*> ParticleSystemComponents;

	// 투사체 관련
	UPROPERTY(VisibleAnywhere)
	UNiagaraSystem* NS_ProjectileCast;

	// ============================================================================================
	// 투사체
	UPROPERTY(EditAnywhere, Category = "Projectile")
	FVector MuzzleOffset;

	UPROPERTY(EditAnywhere, Category = "Projectile")
	TSubclassOf<class AGimmick1_Projectile> ProjectileClass;
};