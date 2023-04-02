// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CharacterState.h"
#include "MotionWarpingComponent.h"
#include "MyCharacter.generated.h"


UCLASS()
class THIRDPERSON_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacter(); //설정 관리 

	
protected:
	// Called when the game starts or when spawned
	virtual void PostInitializeComponents() override; // 설정
	virtual void BeginPlay() override; //이펙트

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	//GetSetMaker(bool , Attacking , IsAttacking);

	bool GetAttacking();

	void UpDown(float Value);
	void LeftRight(float Value);
	void Yaw(float Value);
	
	// 스킬 
	bool check = false;
	double skill_Length=0;
	

	FVector Target_Location; //마우스 스킬시 위치 
	//FVector CharLastLocation;
	FVector Distance_Char_Tar; // 마우스와 캐릭터 사이 차이
	FVector SkillVector; // 스킬로 임시적으로 저장하는 벡터 
	
	void Attack();
	void Parring();
	void Shift();
	void ShiftReleasd();
	

	// 스킬 관리 함수 
	void SkillPress(ECharacterState InputSkill);
	

	UFUNCTION()
	void OnAttackMontageStarted(UAnimMontage* Montage);
	
	UFUNCTION()
	void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);
	
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent;}
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	//캐릭터의 현재 스킬 저장 
	ECharacterState MyCharacterState = ECharacterState::State_None;

	//콤보 이름 저장하기 
	UPROPERTY(VisibleAnywhere, Category=Pawn)
	bool IsAttacking = false;

	UPROPERTY()
	FVector vecMove;
	
	UPROPERTY()
	class UCountessAnimInstance* AnimInstance;

	UPROPERTY()
	class AMakePlayerController* MyControler;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Motion Warping",meta = (AllowPrivateAccess = "true"))
	class UMotionWarpingComponent* MotionWarpComp;
	

	UPROPERTY()
	int32 AttackIndex = 0;
	UPROPERTY()
	int32 AttackIndexQ = 0;
	UPROPERTY()
	int32 AttackIndexE = 0;
	
};	
