// This project is made for a test assignment

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AIRAIController.generated.h"

class UAIPerceptionComponent;
class AAIRToy;

UCLASS()
class AIRACE_API AAIRAIController : public AAIController
{
    GENERATED_BODY()

public:
    AAIRAIController();

    UFUNCTION(BlueprintNativeEvent, Category = "AI")
    void SetTargetToy(const AAIRToy* TargetToy);
    void SetTargetToy_Implementation(const AAIRToy* TargetToy);

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
    TObjectPtr<UAIPerceptionComponent> AIPerceptionComponent;
};
