// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "S5TestingGroundsGameMode.h"
#include "S5TestingGroundsHUD.h"
#include "Player/FirstPersonCharacter.h"
#include "UObject/ConstructorHelpers.h"

AS5TestingGroundsGameMode::AS5TestingGroundsGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Dynamic/Player/Behaviour/FirstPersonCharacter")); 
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AS5TestingGroundsHUD::StaticClass();
}
