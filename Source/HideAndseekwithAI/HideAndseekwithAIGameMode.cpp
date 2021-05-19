// Copyright Epic Games, Inc. All Rights Reserved.

#include "HideAndseekwithAIGameMode.h"
#include "HideAndseekwithAIHUD.h"
#include "HideAndseekwithAICharacter.h"
#include "UObject/ConstructorHelpers.h"

AHideAndseekwithAIGameMode::AHideAndseekwithAIGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AHideAndseekwithAIHUD::StaticClass();
}
