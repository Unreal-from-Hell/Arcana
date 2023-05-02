// Fill out your copyright notice in the Description page of Project Settings.


#include "LightningMonsterAnim.h"

ULightningMonsterAnim::ULightningMonsterAnim()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage> Attack(TEXT("AnimMontage'/Game/ThirdPerson/Blueprints/Monster/ElementalMonster/LightningMonster/Anim/LightningMonster_Attack.LightningMonster_Attack'"));

	if(Attack.Succeeded())
		AttackMontage=Attack.Object;
}
