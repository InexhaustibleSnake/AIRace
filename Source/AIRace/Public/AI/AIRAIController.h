// This project is made for a test assignment

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AIRAIController.generated.h"

class UAIPerceptionComponent;
class AAIRToy;
class AAIRAICharacter;

DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnToyPickedUpSignature, AAIRToy*, PickedupToy, AAIRAIController*, ByAIController);

UCLASS()
class AIRACE_API AAIRAIController : public AAIController
{
    GENERATED_BODY()

public:
    AAIRAIController();

    UFUNCTION(BlueprintNativeEvent, Category = "AI")
    void SetTargetToy(const AAIRToy* TargetToy);
    void SetTargetToy_Implementation(const AAIRToy* TargetToy);

    void ClearTargetToy();

    FOnToyPickedUpSignature OnToyPickedUp;

protected:
    UFUNCTION(BlueprintCallable, Category = "AI")
    void PickupToy(AAIRToy* TargetToy);

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
    TObjectPtr<UAIPerceptionComponent> AIPerceptionComponent;

    UPROPERTY(BlueprintReadOnly, Category = "AI")
    bool ChasingToy = false;
};
