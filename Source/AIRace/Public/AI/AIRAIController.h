// This project is made for a test assignment

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AIRAIController.generated.h"

class UAIPerceptionComponent;

UCLASS()
class AIRACE_API AAIRAIController : public AAIController
{
    GENERATED_BODY()

public:
    AAIRAIController();

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
    TObjectPtr<UAIPerceptionComponent> AIPerceptionComponent;
};
