// This project is made for a test assignment

#include "Logic/PlayerControllers/AIRPlayerController.h"
#include "Logic/GameStates/AIRGameState.h"

void AAIRPlayerController::BeginPlay()
{
    Super::BeginPlay();

    if (GetAIRGameState())
    {
        GetAIRGameState()->OnMatchStateChanged.AddDynamic(this, &AAIRPlayerController::OnMatchStateChanged);
    }
}

void AAIRPlayerController::RestartMatch()
{
    if (!HasAuthority())
    {
        ServerRestartGame();
        return;
    }

    if (!GetAIRGameState()) return;

    GetAIRGameState()->RestartGame();
}

void AAIRPlayerController::ServerRestartGame_Implementation()
{
    RestartMatch();
}

void AAIRPlayerController::OnMatchStateChanged(const MatchState NewState)
{
    bool MatchStarted = NewState == MatchState::Started;

    SetShowMouseCursor(MatchStarted ? false : true);

    MatchStarted ? SetInputMode(FInputModeGameOnly()) : SetInputMode(FInputModeUIOnly());
}

AAIRGameState* AAIRPlayerController::GetAIRGameState() const
{
    return GetWorld() ? Cast<AAIRGameState>(GetWorld()->GetGameState()) : nullptr;
}
