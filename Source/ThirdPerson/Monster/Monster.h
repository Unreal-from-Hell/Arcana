// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "ThirdPerson/Boss1/Boss1Character.h"
#include "Monster.generated.h"

UCLASS()
class THIRDPERSON_API AMonster : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMonster();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void PossessedBy(AController* NewController) override;
	
	virtual void Attack();
	FOnAttackEndDelegate OnAttackEnd;

	float GetHp(){return Hp;};
	void SetHp(float hp){Hp = hp;};
	
protected:
	bool isAttacking=false;
	float Hp=100.f;
	float MaxHp=100.f;
	
	UPROPERTY(VisibleAnywhere, Category=SkeletalMesh)
	class USkeletalMeshComponent* SkeletalMeshComponent;
};
