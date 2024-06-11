// This project is made for a test assignment

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "AIRGameState.generated.h"

UCLASS()
class AIRACE_API AAIRGameState : public AGameStateBase
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "AIRGameState")
    float GetMatchRemainingTime() const { return RemainingMatchTime; }

protected:
    virtual void BeginPlay() override;

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

    void GameTimerUpdate();

    UPROPERTY(meta = (Units = "Seconds"))
    float MatchTime = 60.0f;

    UPROPERTY(Replicated, meta = (Units = "Seconds"))
    float RemainingMatchTime = MatchTime;

    FTimerHandle MatchTimer;
};
