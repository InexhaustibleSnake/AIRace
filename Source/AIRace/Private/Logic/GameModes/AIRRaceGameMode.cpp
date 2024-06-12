// This project is made for a test assignment

#include "Logic/GameModes/AIRRaceGameMode.h"
#include "Logic/PlayerStates/AIRPlayerState.h"
#include "Characters/AIRPlayerCharacter.h"
#include "Characters/AIRAICharacter.h"
#include "AI/AIRAIController.h"
#include "Items/AIRToy.h"
#include "EngineUtils.h"
#include "Logic/GameStates/AIRGameState.h"
#include "Logic/PlayerControllers/AIRPlayerController.h"

AAIRRaceGameMode::AAIRRaceGameMode()
{
    DefaultPawnClass = AAIRPlayerCharacter::StaticClass();
    PlayerStateClass = AAIRPlayerState::StaticClass();
    GameStateClass = AAIRGameState::StaticClass();
    PlayerControllerClass = AAIRPlayerController::StaticClass();
}

void AAIRRaceGameMode::BeginPlay()
{
    Super::BeginPlay();

    for (const auto OneAIController : FindActorsOfClass<AAIRAIController>(AAIRAIController::StaticClass()))
    {
        if (!OneAIController) continue;

        OneAIController->OnToyPickedUp.BindUFunction(this, "OnToyPickedUp");
        OneAIController->OnDestroyed.AddDynamic(this, &AAIRRaceGameMode::OnAIControllerDestroyed);

        AIControllers.Add(OneAIController);
    }

    if (auto AIRGameState = Cast<AAIRGameState>(GameState))
    {
        AIRGameState->OnMatchStateChanged.AddDynamic(this, &AAIRRaceGameMode::OnMatchStateChanged);
    }
}

void AAIRRaceGameMode::OnMatchStateChanged(const MatchState NewState)
{
    if (NewState == MatchState::Ended)
    {
        OnMatchEnded();
    }
}

void AAIRRaceGameMode::OnAIControllerDestroyed(AActor* DestroyedAIActor)
{
    const auto AIController = Cast<AAIRAIController>(DestroyedAIActor);
    if (!AIController) return;

    AIController->OnToyPickedUp.Unbind();
}

void AAIRRaceGameMode::OnNewToySpawned(AAIRToy* NewToy)
{
    if (!NewToy) return;

    NewToy->OnToyUsed.AddDynamic(this, &AAIRRaceGameMode::OnToyUsed);

    Toys.Add(NewToy);
}

void AAIRRaceGameMode::OnToyDestroyed(AAIRToy* DestroyedToy)
{
    if (!DestroyedToy) return;

    DestroyedToy->OnToyUsed.Remove(this, "OnToyUsed");

    if (!Toys.Contains(DestroyedToy)) return;

    Toys.Remove(DestroyedToy);
}

void AAIRRaceGameMode::OnToyUsed(AAIRToy* NewToy)
{
    if (!NewToy) return;

    for (auto OneAIController : AIControllers)
    {
        if (!OneAIController) continue;

        OneAIController->SetTargetToy(NewToy);
    }

    SetCanToysBeUsed(false);
}

void AAIRRaceGameMode::SetCanToysBeUsed(bool CanBeUsed)
{
    for (auto OneToy : Toys)
    {
        if (!OneToy) continue;

        OneToy->SetCanUseToy(CanBeUsed);
    }
}

void AAIRRaceGameMode::OnToyPickedUp(AAIRToy* Toy, AAIRAIController* ByAIController)
{
    SetCanToysBeUsed(true);

    if (!Toy) return;

    Toy->ReturnToy();

    for (auto OneAIController : AIControllers)
    {
        if (!OneAIController) continue;

        OneAIController->ClearTargetToy();
    }

    if (!ByAIController) return;

    const auto AIRPlayerState = ByAIController->GetPlayerState<AAIRPlayerState>();
    if (!AIRPlayerState) return;

    AIRPlayerState->AddScores(Toy->GetToyValue());
}

void AAIRRaceGameMode::RestartGame()
{
    for (auto OneAIController : AIControllers)
    {
        if (!OneAIController) continue;

        const auto AIRPlayerState = OneAIController->GetPlayerState<AAIRPlayerState>();
        if (!AIRPlayerState) continue;

        AIRPlayerState->ClearScore();
    }
}

void AAIRRaceGameMode::OnMatchEnded()
{
    for (auto OneAIController : AIControllers)
    {
        if (!OneAIController) continue;

        OneAIController->ClearTargetToy();
    }

    for (auto OneToy : Toys)
    {
        if (!OneToy || OneToy->GetInHands()) continue;

        OneToy->ReturnToy();
    }

    SetCanToysBeUsed(true);
}
