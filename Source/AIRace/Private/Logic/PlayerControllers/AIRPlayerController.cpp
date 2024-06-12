// This project is made for a test assignment

#include "Logic/PlayerControllers/AIRPlayerController.h"
#include "Logic/GameStates/AIRGameState.h"

void AAIRPlayerController::BeginPlay()
{
    Super::BeginPlay();

    if (GetWorld())
    {
        const auto AIRGameState = Cast<AAIRGameState>(GetWorld()->GetGameState());
        if (!AIRGameState) return;

        AIRGameState->OnMatchStateChanged.AddDynamic(this, &AAIRPlayerController::OnMatchStateChanged);
    }
}

void AAIRPlayerController::OnMatchStateChanged(const MatchState NewState)
{
    bool MatchStarted = NewState == MatchState::Started;

    SetShowMouseCursor(MatchStarted ? false : true);

    MatchStarted ? SetInputMode(FInputModeGameOnly()) : SetInputMode(FInputModeUIOnly());

    if (!MatchStarted)
    {
        StopMovement();
    }
}
