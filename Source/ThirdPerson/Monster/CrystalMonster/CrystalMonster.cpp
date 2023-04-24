// Fill out your copyright notice in the Description page of Project Settings.


#include "CrystalMonster.h"

ACrystalMonster::ACrystalMonster()
{
}

void ACrystalMonster::BeginPlay()
{
	Super::BeginPlay();

	AnimInstance=Cast<UCrystalMonsterAnim>(SkeletalMeshComponent->GetAnimInstance());
	AnimInstance->OnMontageEnded.AddDynamic(this, &ACrystalMonster::OnAttackMontageEnded);
}

void ACrystalMonster::Attack()
{
	Super::Attack();

	AnimInstance->PlayAttackMontagee();
	AnimInstance->JumpToSection();
	// TODO 공격 사운드 및 이펙트
	isAttacking=true;
}

void ACrystalMonster::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	isAttacking=false;
	OnAttackEnd.Broadcast();
}
