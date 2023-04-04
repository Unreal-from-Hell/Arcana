// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// 캐릭터 스킬 열거형 UENUM은 uint8만 지원 

UENUM(BlueprintType)
enum class ECharacterState : uint8
{
	State_None UMETA(DisplayName = "None"),
	State_PrimaryAttack UMETA(DisplayName = "Primary Attack"),
	State_SkillQ UMETA(DisplayName = "SkillQ"),
	State_SkillW UMETA(DisplayName = "SkillW"),
	State_SkillE UMETA(DisplayName = "SkillE"),
	State_SkillR UMETA(DisplayName = "SkillR"),
	State_SkillF UMETA(DisplayName = "SkillF"),
	State_SkillT UMETA(DisplayName = "SkillT"),
	State_Dash UMETA(DisplayName = "Dash"),
	State_Space UMETA(DisplayName = "Space"),
};