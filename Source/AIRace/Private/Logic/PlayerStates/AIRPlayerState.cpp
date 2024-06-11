// This project is made for a test assignment

#include "Logic/PlayerStates/AIRPlayerState.h"

void AAIRPlayerState::AddScores(float Amount)
{
    SetScore(GetScore() + Amount);
    OnRep_Score();
}

void AAIRPlayerState::OnRep_Score()
{
    OnScoreChanged.Broadcast(GetScore());
}
