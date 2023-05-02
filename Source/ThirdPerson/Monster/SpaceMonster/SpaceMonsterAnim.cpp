// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceMonsterAnim.h"

USpaceMonsterAnim::USpaceMonsterAnim()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage> Attack(TEXT("AnimMontage'/Game/ThirdPerson/Blueprints/Monster/ElementalMonster/SpaceMonster/Anim/SpaceMonster_Attack.SpaceMonster_Attack'"));

	if(Attack.Succeeded())
		AttackMontage=Attack.Object;
}
