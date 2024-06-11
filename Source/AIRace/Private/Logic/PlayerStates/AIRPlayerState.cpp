// This project is made for a test assignment

#include "Logic/PlayerStates/AIRPlayerState.h"

void AAIRPlayerState::OnRep_Score() 
{
    OnScoreChanged.Broadcast(Score);
}
