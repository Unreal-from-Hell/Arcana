// Fill out your copyright notice in the Description page of Project Settings.


#include "DarknessMonster.h"

ADarknessMonster::ADarknessMonster()
{
}

void ADarknessMonster::BeginPlay()
{
	Super::BeginPlay();

	AnimInstance=Cast<UDarknessMonsterAnim>(SkeletalMeshComponent->GetAnimInstance());
	AnimInstance->OnMontageEnded.AddDynamic(this, &ADarknessMonster::OnAttackMontageEnded);
}

void ADarknessMonster::Attack()
{
	Super::Attack();
	
	if(isAttacking)
		return;
	
	AnimInstance->PlayAttackMontagee();
	AnimInstance->JumpToSection();
	// TODO 공격 사운드 및 이펙트
	isAttacking=true;
}

void ADarknessMonster::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	isAttacking=false;
	OnAttackEnd.Broadcast();
}
