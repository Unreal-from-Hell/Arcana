// Fill out your copyright notice in the Description page of Project Settings.


#include "StoneMonsterAnim.h"

UStoneMonsterAnim::UStoneMonsterAnim()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage> Attack(TEXT("AnimMontage'/Game/ThirdPerson/Blueprints/Monster/ElementalMonster/StoneMonster/Anim/StoneMonster_Attack.StoneMonster_Attack'"));

	if(Attack.Succeeded())
		AttackMontage=Attack.Object;
}
