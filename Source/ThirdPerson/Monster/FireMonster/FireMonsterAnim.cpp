// Fill out your copyright notice in the Description page of Project Settings.


#include "FireMonsterAnim.h"

UFireMonsterAnim::UFireMonsterAnim()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage> Attack(TEXT("AnimMontage'/Game/ThirdPerson/Blueprints/Monster/ElementalMonster/FireMonster/Anim/FireMonster_Attack.FireMonster_Attack'"));

	if(Attack.Succeeded())
		AttackMontage=Attack.Object;
}
