// Fill out your copyright notice in the Description page of Project Settings.


#include "LightMonsterAnim.h"

ULightMonsterAnim::ULightMonsterAnim()
{
	ConstructorHelpers::FObjectFinder<UAnimMontage> Attack(TEXT("AnimMontage'/Game/ThirdPerson/Blueprints/Monster/ElementalMonster/LightMonster/Anim/LightMonster_Attack.LightMonster_Attack'"));

	if(Attack.Succeeded())
		AttackMontage=Attack.Object;
}
