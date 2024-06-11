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

    template <typename T>
    TArray<T*> FindActorsOfClass(const TSubclassOf<AActor> ActorClass)
    {
        if (!GetWorld()) return TArray<T*>();

        TArray<T*> ReceivedActors;

        for (TActorIterator<T> OneActor(GetWorld()); OneActor; ++OneActor)
        {
            if (!OneActor) continue;

            ReceivedActors.Add(*OneActor);
        }

        return ReceivedActors;
    }

    TArray<AAIRAIController*> GetAIControllers() const;

    TArray<AAIRAIController*> AIControllers;

    TArray<AAIRToy*> Toys;
};
