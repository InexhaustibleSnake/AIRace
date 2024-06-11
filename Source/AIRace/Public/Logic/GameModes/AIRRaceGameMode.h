// This project is made for a test assignment

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "AIRRaceGameMode.generated.h"

class AAIRToy;
class AAIRAICharacter;
class AAIRAIController;

UCLASS()
class AIRACE_API AAIRRaceGameMode : public AGameModeBase
{
    GENERATED_BODY()

public:
    AAIRRaceGameMode();

    void OnNewToySpawned(AAIRToy* NewToy);
    void OnToyDestroyed(AAIRToy* DestroyedToy);

    UFUNCTION()
    void OnToyPickedUp(AAIRToy* Toy, AAIRAICharacter* ByAICharacter);

protected:
    virtual void BeginPlay() override;

    UFUNCTION()
    void OnAIControllerDestroyed(AActor* DestroyedAIActor);

    UFUNCTION()
    void OnToyUsed(AAIRToy* NewToy);

    TArray<AAIRAIController*> GetAIControllers() const;
};
