// This project is made for a test assignment

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Logic/GameStates/AIRGameState.h"
#include "AIRPlayerController.generated.h"

UCLASS()
class AIRACE_API AAIRPlayerController : public APlayerController
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "AIRPlayerController")
    void RestartMatch();

protected:
    virtual void BeginPlay() override;

    UFUNCTION(Server, Reliable)
    void ServerRestartGame();
    void ServerRestartGame_Implementation();

    UFUNCTION()
    void OnMatchStateChanged(const MatchState NewState);

    AAIRGameState* GetAIRGameState() const;
};
