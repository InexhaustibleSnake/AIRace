// This project is made for a test assignment

#include "Logic/GameModes/AIRRaceGameMode.h"
#include "Characters/AIRPlayerCharacter.h"

AAIRRaceGameMode::AAIRRaceGameMode()
{
    DefaultPawnClass = AAIRPlayerCharacter::StaticClass();
}
