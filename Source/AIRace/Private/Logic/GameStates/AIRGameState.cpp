// This project is made for a test assignment

#include "Logic/GameStates/AIRGameState.h"
#include "Net/UnrealNetwork.h"
#include "Logic/GameModes/AIRRaceGameMode.h"

void AAIRGameState::BeginPlay()
{
    Super::BeginPlay();

    StartTimer();
}

void AAIRGameState::RestartGame()
{
    OnMatchStateChanged.Broadcast(MatchState::Started);

    if (GetWorld())
    {
        auto AIRGameMode = Cast<AAIRRaceGameMode>(GetWorld()->GetAuthGameMode());

        if (AIRGameMode)
        {
            AIRGameMode->RestartGame();
        }
    }

    ResetTimer();
}

void AAIRGameState::StartTimer()
{
    GetWorldTimerManager().SetTimer(MatchTimer, this, &AAIRGameState::GameTimerUpdate, 1.0f, true);
}

void AAIRGameState::GameTimerUpdate()
{
    RemainingMatchTime = FMath::Clamp(--RemainingMatchTime, 0, MatchTime);

    if (!FMath::IsNearlyZero(RemainingMatchTime)) return;

    GetWorldTimerManager().ClearTimer(MatchTimer);

    OnMatchStateChanged.Broadcast(MatchState::Ended);
}

void AAIRGameState::ResetTimer()
{
    RemainingMatchTime = MatchTime;

    StartTimer();
}

void AAIRGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME_CONDITION(AAIRGameState, RemainingMatchTime, COND_InitialOnly);
}
