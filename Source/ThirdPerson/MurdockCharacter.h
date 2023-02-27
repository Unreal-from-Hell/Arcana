// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MurdockCharacter.generated.h"

UCLASS()
class THIRDPERSON_API AMurdockCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMurdockCharacter();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


protected:
	// 마우스 관련 함수
	// ========================================
	void Yaw(float Value);
	void Pitch(float Value);
	// 움직임 관련 함수
	// ========================================
	// 걷기
	void MoveForward(float Value);
	void MoveRight(float Value);
	// 달리기
	void Sprint();
	void StopSprint();
	// 천천히 걷기
	void Walking();
	void StopWalking();
	
	// 공격 관련 함수
	// ========================================
	// 기본 공격
	void Attack();

	// 스킬 공격
	void SKill_1();
	void SKill_2();
	void SKill_3();
	void SKill_4();
	// 애니메이션 관련 함수
	// ========================================
	// 기본 공격 종료 시
	UFUNCTION()
	void OnAttackMontageEended(UAnimMontage* Montage, bool bInterrupted);

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return _springArm; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return _camera; }
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	// 블렌드 스페이스 관련 변수
	UPROPERTY()
	float _vertical=0.f;
	
	UPROPERTY()
	float _horizental=0.f;
	
private:
	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* _springArm;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* _camera;

	UPROPERTY(VisibleAnywhere)
	bool _isAttacking = false;
	
	UPROPERTY()
	class UMyAnimInstance* _animInstance;
};
