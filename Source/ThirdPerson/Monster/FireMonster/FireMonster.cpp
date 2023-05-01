// Fill out your copyright notice in the Description page of Project Settings.


#include "FireMonster.h"

AFireMonster::AFireMonster()
{
}

void AFireMonster::BeginPlay()
{
	Super::BeginPlay();

	AnimInstance=Cast<UFireMonsterAnim>(SkeletalMeshComponent->GetAnimInstance());
	AnimInstance->OnMontageEnded.AddDynamic(this, &AFireMonster::OnAttackMontageEnded);
}

void AFireMonster::Attack()
{
	Super::Attack();

	if(isAttacking)
		return;

	AnimInstance->PlayAttackMontagee();
	AnimInstance->JumpToSection();
	// TODO 공격 사운드 및 이펙트
	isAttacking=true;
}

void AFireMonster::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	isAttacking=false;
	OnAttackEnd.Broadcast();
}
