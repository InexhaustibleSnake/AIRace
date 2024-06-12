// This project is made for a test assignment

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "AIRGameState.generated.h"

UENUM(BlueprintType)
enum class MatchState : uint8
{
    Started,
    Ended
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMatchStateChangedSignature, MatchState, NewState);

UCLASS()
class AIRACE_API AAIRGameState : public AGameStateBase
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "AIRGameState")
    void StartTimer();

    UFUNCTION(BlueprintCallable, Category = "AIRGameState")
    float GetMatchRemainingTime() const { return RemainingMatchTime; }

    UFUNCTION(BlueprintCallable, Category = "AIRGameState")
    void RestartGame();

    UPROPERTY(BlueprintAssignable, Category = "AIRGameState")
    FOnMatchStateChangedSignature OnMatchStateChanged;

protected:
    virtual void BeginPlay() override;

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;



    void GameTimerUpdate();

    void ResetTimer();

    UFUNCTION()
    void OnRep_MatchState();

    UPROPERTY(EditDefaultsOnly, meta = (Units = "Seconds"), meta = (ClampMin = "10"))
    float MatchTime = 60.0f;

    UPROPERTY(Replicated, meta = (Units = "Seconds"))
    float RemainingMatchTime = MatchTime;

    UPROPERTY(ReplicatedUsing = OnRep_MatchState)
    MatchState CurrentMatchState;

    FTimerHandle MatchTimer;
};
