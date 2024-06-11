// This project is made for a test assignment

#include "Logic/GameStates/AIRGameState.h"
#include "Net/UnrealNetwork.h"

void AAIRGameState::BeginPlay()
{
    Super::BeginPlay();

    GetWorldTimerManager().SetTimer(MatchTimer, this, &AAIRGameState::GameTimerUpdate, 1.0f, true);
}

void AAIRGameState::GameTimerUpdate()
{
    --RemainingMatchTime;
}

void AAIRGameState::AddPlayerState(APlayerState* PlayerState)
{
    Super::AddPlayerState(PlayerState);

    OnPlayerStateAdded.Broadcast(PlayerState);
}

void AAIRGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME_CONDITION(AAIRGameState, RemainingMatchTime, COND_InitialOnly);
}
