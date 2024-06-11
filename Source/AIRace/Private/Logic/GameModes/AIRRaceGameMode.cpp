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

    for (const auto OneAIController : FindActorsOfClass<AAIRAIController>(AAIRAIController::StaticClass()))
    {
        if (!OneAIController) continue;

        OneAIController->OnToyPickedUp.BindUFunction(this, "OnToyPickedUp");
        OneAIController->OnDestroyed.AddDynamic(this, &AAIRRaceGameMode::OnAIControllerDestroyed);

        AIControllers.Add(OneAIController);
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
    SetCanToysBeUsed(true);

    if (!Toy) return;

    Toy->ReturnToy();

    for (auto OneAIController : FindActorsOfClass<AAIRAIController>(AAIRAIController::StaticClass()))
    {
        if (!OneAIController) continue;

        OneAIController->ClearTargetToy();
    }

    if (!ByAICharacter) return;

    ByAICharacter->AddScores(ByAICharacter->GetScores() + Toy->GetToyValue());
}
