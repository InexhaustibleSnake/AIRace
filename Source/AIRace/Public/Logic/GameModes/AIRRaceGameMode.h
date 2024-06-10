// This project is made for a test assignment

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "AIRRaceGameMode.generated.h"

class AAIRToy;

UCLASS()
class AIRACE_API AAIRRaceGameMode : public AGameModeBase
{
    GENERATED_BODY()

public:
    AAIRRaceGameMode();

    void OnNewToySpawned(AAIRToy* NewToy);
    void OnToyDestroyed(AAIRToy* DestroyedToy);

protected:
    UFUNCTION()
    void OnToyUsed(AAIRToy* NewToy);
};
