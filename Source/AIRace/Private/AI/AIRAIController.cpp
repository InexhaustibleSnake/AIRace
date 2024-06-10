// This project is made for a test assignment

#include "AI/AIRAIController.h"
#include "Perception/AIPerceptionComponent.h"

AAIRAIController::AAIRAIController() 
{
    AIPerceptionComponent = CreateDefaultSubobject <UAIPerceptionComponent>("AIPerceptionComponent");
}
