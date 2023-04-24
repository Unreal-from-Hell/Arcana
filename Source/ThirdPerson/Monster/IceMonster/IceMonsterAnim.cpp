// Fill out your copyright notice in the Description page of Project Settings.


#include "IceMonsterAnim.h"

UIceMonsterAnim::UIceMonsterAnim()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage> Attack(TEXT("AnimMontage'/Game/ThirdPerson/Blueprints/Monster/ElementalMonster/IceMonster/Anim/IceMonster_Attack.IceMonster_Attack'"));

	if(Attack.Succeeded())
		AttackMontage=Attack.Object;
}

