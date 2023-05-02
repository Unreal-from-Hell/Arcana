// Fill out your copyright notice in the Description page of Project Settings.


#include "WaterMonsterAnim.h"

UWaterMonsterAnim::UWaterMonsterAnim()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage> Attack(TEXT("AnimMontage'/Game/ThirdPerson/Blueprints/Monster/ElementalMonster/WaterMonster/Anim/WaterMonster_Attack.WaterMonster_Attack'"));

	if(Attack.Succeeded())
		AttackMontage=Attack.Object;
}
