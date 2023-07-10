// Copyright Epic Games, Inc. All Rights Reserved.

#include "ArcActivityExampleGameMode.h"
#include "ArcActivityExampleCharacter.h"
#include "UObject/ConstructorHelpers.h"

AArcActivityExampleGameMode::AArcActivityExampleGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
