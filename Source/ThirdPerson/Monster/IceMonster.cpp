// Fill out your copyright notice in the Description page of Project Settings.


#include "IceMonster.h"

#include "IceMonsterAnim.h"

AIceMonster::AIceMonster()
{
}

void AIceMonster::BeginPlay()
{
	Super::BeginPlay();

	AnimInstance=Cast<UIceMonsterAnim>(SkeletalMeshComponent->GetAnimInstance());
	AnimInstance->OnMontageEnded.AddDynamic(this, &AIceMonster::OnAttackMontageEnded);
}

void AIceMonster::Attack()
{
	if(isAttacking)
		return;

	AnimInstance->PlayAttackMontagee();
	AnimInstance->JumpToSection();
	// TODO 공격 사운드 및 이펙트
	isAttacking=true;
}

void AIceMonster::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	isAttacking=false;
	OnAttackEnd.Broadcast();
}
