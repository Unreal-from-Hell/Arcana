// Fill out your copyright notice in the Description page of Project Settings.


#include "ShadowMonsterAnim.h"

UShadowMonsterAnim::UShadowMonsterAnim()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage> Attack(TEXT("AnimMontage'/Game/ThirdPerson/Blueprints/Monster/ElementalMonster/ShadowMonster/Anim/ShadowMonster_Attack.ShadowMonster_Attack'"));

	if(Attack.Succeeded())
		AttackMontage=Attack.Object;
}
