// This project is made for a test assignment

#include "AI/AIRAIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "Characters/AIRAICharacter.h"

AAIRAIController::AAIRAIController()
{
    AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>("AIPerceptionComponent");
}

void AAIRAIController::SetTargetToy_Implementation(const AAIRToy* TargetToy) 
{
    ChasingToy = true;
}

void AAIRAIController::ClearTargetToy()
{
    ChasingToy = false;
}

void AAIRAIController::PickupToy(AAIRToy* TargetToy)
{
    const auto ControlledPawn = Cast<AAIRAICharacter>(GetPawn());

    OnToyPickedUp.ExecuteIfBound(TargetToy, ControlledPawn);
}
