// Fill out your copyright notice in the Description page of Project Settings.


#include "LightMonster.h"

ALightMonster::ALightMonster()
{
}

void ALightMonster::BeginPlay()
{
	Super::BeginPlay();

	//AnimInstance=Cast<ULightMonsterAnim>(SkeletalMeshComponent->GetAnimInstance());
	//AnimInstance->OnMontageEnded.AddDynamic(this, &ALightMonster::OnAttackMontageEnded);
}

void ALightMonster::Attack()
{
	Super::Attack();

	if(isAttacking)
		return;
	
	//AnimInstance->PlayAttackMontagee();
	//AnimInstance->JumpToSection();
	// TODO 공격 사운드 및 이펙트
	isAttacking=true;
}

void ALightMonster::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	isAttacking=false;
	OnAttackEnd.Broadcast();
}
