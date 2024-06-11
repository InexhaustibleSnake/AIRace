// This project is made for a test assignment

#include "Logic/GameModes/AIRRaceGameMode.h"
#include "Characters/AIRPlayerCharacter.h"
#include "Characters/AIRAICharacter.h"
#include "AI/AIRAIController.h"
#include "Items/AIRToy.h"
#include "EngineUtils.h"

AAIRRaceGameMode::AAIRRaceGameMode()
{
    DefaultPawnClass = AAIRPlayerCharacter::StaticClass();
}

void AAIRRaceGameMode::BeginPlay()
{
    Super::BeginPlay();

    for (const auto OneAIController : GetAIControllers())
    {
        if (!OneAIController) continue;

        OneAIController->OnToyPickedUp.BindUFunction(this, "OnToyPickedUp");
        OneAIController->OnDestroyed.AddDynamic(this, &AAIRRaceGameMode::OnAIControllerDestroyed);
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
}

void AAIRRaceGameMode::OnToyDestroyed(AAIRToy* DestroyedToy)
{
    if (!DestroyedToy) return;

    DestroyedToy->OnToyUsed.Remove(this, "OnToyUsed");
}

void AAIRRaceGameMode::OnToyUsed(AAIRToy* NewToy)
{
    if (!NewToy) return;

    for (auto OneAIController : GetAIControllers())
    {
        if (!OneAIController) continue;

        OneAIController->SetTargetToy(NewToy);
    }
}

TArray<AAIRAIController*> AAIRRaceGameMode::GetAIControllers() const
{
    if (!GetWorld()) return TArray<AAIRAIController*>();

    TArray<AAIRAIController*> ReceivedAIControllers;

    for (TActorIterator<AAIRAIController> OneAIController(GetWorld()); OneAIController; ++OneAIController)
    {
        if (!OneAIController) continue;

        ReceivedAIControllers.Add(*OneAIController);
    }

    return ReceivedAIControllers;
}

void AAIRRaceGameMode::OnToyPickedUp(AAIRToy* Toy, AAIRAICharacter* ByAICharacter)
{
    if (!Toy) return;

    Toy->ReturnToy();

    for (auto OneAIController : GetAIControllers())
    {
        if (!OneAIController) continue;

        OneAIController->ClearTargetToy();
    }

    if (!ByAICharacter) return;

    ByAICharacter->AddScores(ByAICharacter->GetScores() + Toy->GetToyValue());
}
