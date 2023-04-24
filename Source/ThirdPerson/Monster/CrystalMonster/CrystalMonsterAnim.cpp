// Fill out your copyright notice in the Description page of Project Settings.


#include "CrystalMonsterAnim.h"

UCrystalMonsterAnim::UCrystalMonsterAnim()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage> Attack(TEXT("AnimMontage'/Game/ThirdPerson/Blueprints/Monster/ElementalMonster/CrystalMonster/Anim/CrystalMonster_Attack.CrystalMonster_Attack'"));

	if(Attack.Succeeded())
		AttackMontage=Attack.Object;
}
