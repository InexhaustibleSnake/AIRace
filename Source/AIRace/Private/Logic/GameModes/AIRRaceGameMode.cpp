// This project is made for a test assignment

#include "Logic/GameModes/AIRRaceGameMode.h"
#include "Characters/AIRPlayerCharacter.h"
#include "AI/AIRAIController.h"
#include "Items/AIRToy.h"
#include "EngineUtils.h"

AAIRRaceGameMode::AAIRRaceGameMode()
{
    DefaultPawnClass = AAIRPlayerCharacter::StaticClass();
}

void AAIRRaceGameMode::OnNewToySpawned(AAIRToy* NewToy)
{
    if (!NewToy) return;

    NewToy->OnToyUsed.AddDynamic(this, &AAIRRaceGameMode::OnToyUsed);
}

void AAIRRaceGameMode::OnToyDestroyed(AAIRToy* DestroyedToy) 
{
    if (!DestroyedToy) return;

    DestroyedToy->OnToyUsed.Remove(this, "OnToyUsed");
}

void AAIRRaceGameMode::OnToyUsed(AAIRToy* NewToy)
{
    if (!NewToy) return;

    for (TActorIterator<AAIRAIController> OneAIController(GetWorld()); OneAIController; ++OneAIController)
    {
        if (!OneAIController) continue;

        OneAIController->SetTargetToy(NewToy);
    }
}
