// This project is made for a test assignment

#include "AI/AIRAIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "Logic/GameModes/AIRRaceGameMode.h"
#include "Characters/AIRAICharacter.h"

AAIRAIController::AAIRAIController()
{
    AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>("AIPerceptionComponent");
}

void AAIRAIController::SetTargetToy_Implementation(const AAIRToy* TargetToy) {}

void AAIRAIController::PickupToy(AAIRToy* TargetToy)
{
    const auto ControlledPawn = Cast<AAIRAICharacter>(GetPawn());

    OnToyPickedUp.ExecuteIfBound(TargetToy, ControlledPawn);
}
