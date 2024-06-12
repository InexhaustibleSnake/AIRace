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

    InHands = false;

    OnRep_InHands();
}

void AAIRToy::SeconderyUse()
{
    ToyDataIndex = ++ToyDataIndex % DefaultToyData.Num();

    OnRep_ToyDataIndex();
}

void AAIRToy::ThrowToy()
{
    if (!ItemMeshComponent) return;

    ItemMeshComponent->SetSimulatePhysics(true);

    ItemMeshComponent->SetPhysicsLinearVelocity(GetLaunchVelocity());

    ItemMeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

    DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

    OnToyUsed.Broadcast(this);
}

void AAIRToy::ReturnToy()
{
    InHands = true;

    OnRep_InHands();
}

void AAIRToy::OnRep_InHands()
{
    InHands ? AttachToOwner() : ThrowToy();
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

bool AAIRToy::CanUseItem() const
{
    return InHands && CanUseToy;
}

void AAIRToy::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(AAIRToy, InHands);
    DOREPLIFETIME(AAIRToy, ToyDataIndex);
}