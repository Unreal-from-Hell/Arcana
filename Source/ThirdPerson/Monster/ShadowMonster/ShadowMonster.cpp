// Fill out your copyright notice in the Description page of Project Settings.


#include "ShadowMonster.h"

AShadowMonster::AShadowMonster()
{
}

void AShadowMonster::BeginPlay()
{
	Super::BeginPlay();

	AnimInstance=Cast<UShadowMonsterAnim>(SkeletalMeshComponent->GetAnimInstance());
	AnimInstance->OnMontageEnded.AddDynamic(this, &AShadowMonster::OnAttackMontageEnded);
}

void AShadowMonster::Attack()
{
	Super::Attack();
	
	if(isAttacking)
		return;

	AnimInstance->PlayAttackMontagee();
	AnimInstance->JumpToSection();
	// TODO 공격 사운드 및 이펙트
	isAttacking=true;
}

void AShadowMonster::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	isAttacking=false;
	OnAttackEnd.Broadcast();
}
