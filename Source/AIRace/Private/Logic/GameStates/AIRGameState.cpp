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
    if (GetWorld())
    {
        auto AIRGameMode = Cast<AAIRRaceGameMode>(GetWorld()->GetAuthGameMode());

        if (AIRGameMode)
        {
            AIRGameMode->RestartGame();
        }
    }

    SetMatchState(MatchState::Started);
}

void AAIRGameState::StartTimer()
{
    RemainingMatchTime = MatchTime;

    GetWorldTimerManager().SetTimer(MatchTimer, this, &AAIRGameState::GameTimerUpdate, 1.0f, true);
}

void AAIRGameState::GameTimerUpdate()
{
    RemainingMatchTime = FMath::Clamp(--RemainingMatchTime, 0, MatchTime);

    if (!FMath::IsNearlyZero(RemainingMatchTime)) return;

    GetWorldTimerManager().ClearTimer(MatchTimer);

    SetMatchState(MatchState::Ended);
}

void AAIRGameState::ResetTimer()
{
    RemainingMatchTime = MatchTime;

    StartTimer();
}

void AAIRGameState::SetMatchState(const MatchState NewState) 
{
    CurrentMatchState = NewState;
    OnRep_MatchState();
}

void AAIRGameState::OnRep_MatchState()
{
    OnMatchStateChanged.Broadcast(CurrentMatchState);

    if (CurrentMatchState == MatchState::Started)
    {
        ResetTimer();
    }
}

void AAIRGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME_CONDITION(AAIRGameState, RemainingMatchTime, COND_InitialOnly);
    DOREPLIFETIME(AAIRGameState, CurrentMatchState);
}
