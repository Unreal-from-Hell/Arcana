// Fill out your copyright notice in the Description page of Project Settings.


#include "DarknessMonsterAnim.h"

UDarknessMonsterAnim::UDarknessMonsterAnim()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage> Attack(TEXT("AnimMontage'/Game/ThirdPerson/Blueprints/Monster/ElementalMonster/DarknessMonster/Anim/DarknessMonster_Attack.DarknessMonster_Attack'"));

	if(Attack.Succeeded())
		AttackMontage=Attack.Object;
}
