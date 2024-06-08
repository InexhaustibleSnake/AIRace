// Fill out your copyright notice in the Description page of Project Settings.

#include "Logic/GameModes/AIRRaceGameMode.h"
#include "Characters/AIRPlayerCharacter.h"

AAIRRaceGameMode::AAIRRaceGameMode()
{
    DefaultPawnClass = AAIRPlayerCharacter::StaticClass();
}
