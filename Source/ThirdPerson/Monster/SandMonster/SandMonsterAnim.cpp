// Fill out your copyright notice in the Description page of Project Settings.


#include "SandMonsterAnim.h"

USandMonsterAnim::USandMonsterAnim()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage> Attack(TEXT("AnimMontage'/Game/ThirdPerson/Blueprints/Monster/ElementalMonster/SandMonster/Anim/SandMonster_Attack.SandMonster_Attack'"));

	if(Attack.Succeeded())
		AttackMontage=Attack.Object;
}
