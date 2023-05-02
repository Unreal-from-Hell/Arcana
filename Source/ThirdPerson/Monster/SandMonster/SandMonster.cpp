// Fill out your copyright notice in the Description page of Project Settings.


#include "SandMonster.h"

ASandMonster::ASandMonster()
{
}

void ASandMonster::BeginPlay()
{
	Super::BeginPlay();

	AnimInstance=Cast<USandMonsterAnim>(SkeletalMeshComponent->GetAnimInstance());
	AnimInstance->OnMontageEnded.AddDynamic(this, &ASandMonster::OnAttackMontageEnded);
}

void ASandMonster::Attack()
{
	Super::Attack();

	if(isAttacking)
		return;

	AnimInstance->PlayAttackMontagee();
	AnimInstance->JumpToSection();
	// TODO 공격 사운드 및 이펙트
	isAttacking=true;
}

void ASandMonster::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	isAttacking=false;
	OnAttackEnd.Broadcast();
}
