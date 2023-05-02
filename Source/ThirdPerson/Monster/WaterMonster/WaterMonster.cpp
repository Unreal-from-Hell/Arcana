// Fill out your copyright notice in the Description page of Project Settings.


#include "WaterMonster.h"

AWaterMonster::AWaterMonster()
{
}

void AWaterMonster::BeginPlay()
{
	Super::BeginPlay();

	AnimInstance=Cast<UWaterMonsterAnim>(SkeletalMeshComponent->GetAnimInstance());
	AnimInstance->OnMontageEnded.AddDynamic(this, &AWaterMonster::OnAttackMontageEnded);
}

void AWaterMonster::Attack()
{
	Super::Attack();

	if(isAttacking)
		return;

	AnimInstance->PlayAttackMontagee();
	AnimInstance->JumpToSection();
	// TODO 공격 사운드 및 이펙트
	isAttacking=true;
}

void AWaterMonster::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	isAttacking=false;
	OnAttackEnd.Broadcast();
}
