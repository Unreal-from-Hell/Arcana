// Copyright Epic Games, Inc. All Rights Reserved.

#include "ThirdPersonGameMode.h"

#include "MurdockCharacter.h"
#include "ThirdPersonCharacter.h"
#include "Character/MyCharacter.h"
#include "UObject/ConstructorHelpers.h"

AThirdPersonGameMode::AThirdPersonGameMode()
{
	
	DefaultPawnClass=AMyCharacter::StaticClass();

}
