// This project is made for a test assignment

#include "Logic/PlayerControllers/AIRPlayerController.h"
#include "Logic/GameStates/AIRGameState.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

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

    if (GetCharacter() && GetCharacter()->GetCharacterMovement())
    {
        GetCharacter()->GetCharacterMovement()->SetMovementMode(MatchStarted ? EMovementMode::MOVE_Walking : EMovementMode::MOVE_None);
    }

    SetShowMouseCursor(!MatchStarted);

    MatchStarted ? SetInputMode(FInputModeGameOnly()) : SetInputMode(FInputModeUIOnly());
}

AAIRGameState* AAIRPlayerController::GetAIRGameState() const
{
    return GetWorld() ? Cast<AAIRGameState>(GetWorld()->GetGameState()) : nullptr;
}
