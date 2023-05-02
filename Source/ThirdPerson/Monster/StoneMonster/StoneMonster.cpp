// Fill out your copyright notice in the Description page of Project Settings.


#include "StoneMonster.h"

AStoneMonster::AStoneMonster()
{
}

void AStoneMonster::BeginPlay()
{
	Super::BeginPlay();

	AnimInstance=Cast<UStoneMonsterAnim>(SkeletalMeshComponent->GetAnimInstance());
	AnimInstance->OnMontageEnded.AddDynamic(this, &AStoneMonster::OnAttackMontageEnded);
}

void AStoneMonster::Attack()
{
	Super::Attack();

	if(isAttacking)
		return;

	AnimInstance->PlayAttackMontagee();
	AnimInstance->JumpToSection();
	// TODO 공격 사운드 및 이펙트
	isAttacking=true;
}

void AStoneMonster::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	isAttacking=false;
	OnAttackEnd.Broadcast();
}
