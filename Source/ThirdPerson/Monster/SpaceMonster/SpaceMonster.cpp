// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceMonster.h"

ASpaceMonster::ASpaceMonster()
{
}

void ASpaceMonster::BeginPlay()
{
	Super::BeginPlay();

	AnimInstance=Cast<USpaceMonsterAnim>(SkeletalMeshComponent->GetAnimInstance());
	AnimInstance->OnMontageEnded.AddDynamic(this, &ASpaceMonster::OnAttackMontageEnded);
}

void ASpaceMonster::Attack()
{
	Super::Attack();

	if(isAttacking)
		return;

	AnimInstance->PlayAttackMontagee();
	AnimInstance->JumpToSection();
	// TODO 공격 사운드 및 이펙트
	isAttacking=true;
}

void ASpaceMonster::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	isAttacking=false;
	OnAttackEnd.Broadcast();
}
