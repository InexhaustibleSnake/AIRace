// This project is made for a test assignment

#include "AI/AIRAIController.h"
#include "Perception/AIPerceptionComponent.h"

AAIRAIController::AAIRAIController()
{
    AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>("AIPerceptionComponent");

    bWantsPlayerState = true;
}

void AAIRAIController::SetTargetToy_Implementation(const AAIRToy* TargetToy)
{
    ChasingToy = true;
}

void AAIRAIController::ClearTargetToy()
{
    ChasingToy = false;
    StopMovement();
}

void AAIRAIController::PickupToy(AAIRToy* TargetToy)
{
    OnToyPickedUp.ExecuteIfBound(TargetToy, this);
}
