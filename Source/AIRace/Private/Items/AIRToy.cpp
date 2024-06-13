// This project is made for a test assignment

#include "Items/AIRToy.h"

#include "Characters/AIRPlayerCharacter.h"
#include "Logic/GameModes/AIRRaceGameMode.h"

#include "Net/UnrealNetwork.h"

void AAIRToy::BeginPlay()
{
    Super::BeginPlay();

    if (GetGameMode())
    {
        GetGameMode()->OnNewToySpawned(this);
    }

    OnRep_ToyDataIndex();
}

void AAIRToy::SetToyData(int32 DataIndex)
{
    if (!DefaultToyData.IsValidIndex(DataIndex)) return;

    ToyValue = DefaultToyData[DataIndex].Value;

    if (!ItemMeshComponent) return;
    ItemMeshComponent->SetStaticMesh(DefaultToyData[DataIndex].ToyStaticMesh);
}

void AAIRToy::PrimaryUse()
{
    if (!CanUseItem()) return;

    SetInHands(false);
}

void AAIRToy::SeconderyUse()
{
    if (!GetInHands()) return;

    ToyDataIndex = ++ToyDataIndex % DefaultToyData.Num();

    OnRep_ToyDataIndex();
}

void AAIRToy::ThrowToy()
{
    if (!ItemMeshComponent) return;

    ItemMeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

    ItemMeshComponent->SetSimulatePhysics(true);

    ItemMeshComponent->SetPhysicsLinearVelocity(GetLaunchVelocity());

    DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

    OnToyUsed.Broadcast(this);
}

void AAIRToy::ReturnToy()
{
    SetInHands(true);
}

void AAIRToy::OnRep_InHands()
{
    GetInHands() ? AttachToOwner() : ThrowToy();
}

void AAIRToy::OnRep_ToyDataIndex()
{
    SetToyData(ToyDataIndex);
}

AAIRRaceGameMode* AAIRToy::GetGameMode() const
{
    return GetWorld() ? Cast<AAIRRaceGameMode>(GetWorld()->GetAuthGameMode()) : nullptr;
}

FVector AAIRToy::GetLaunchVelocity() const
{
    if (!GetOwnerCharacter()) return FVector();

    FRotator LaunchRotation = GetOwnerCharacter()->GetBaseAimRotation();

    FVector LaunchVelocity = LaunchRotation.Vector() * ThrowDistance;

    return LaunchVelocity;
}

void AAIRToy::SetCanUseToy(bool CanUse)
{
    CanUseToy = CanUse;
}

void AAIRToy::SetInHands(bool bInHands)
{
    InHands = bInHands;

    OnRep_InHands();
}

bool AAIRToy::CanUseItem() const
{
    return GetInHands() && GetCanUseToy();
}

void AAIRToy::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(AAIRToy, InHands);
    DOREPLIFETIME(AAIRToy, ToyDataIndex);
}