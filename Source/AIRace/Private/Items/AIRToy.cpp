// This project is made for a test assignment

#include "Items/AIRToy.h"

#include "Characters/AIRPlayerCharacter.h"

#include "Net/UnrealNetwork.h"

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
    if (!CanUseItem()) return;

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
}

void AAIRToy::ReturnToy()
{
    if (!GetOwnerCharacter()) return;

    const auto AttachComponent = GetOwnerCharacter()->GetItemAttachComponent();

    AttachToOwner();
}

void AAIRToy::OnRep_InHands()
{
    InHands ? ReturnToy() : ThrowToy();
}

void AAIRToy::OnRep_ToyDataIndex()
{
    SetToyData(ToyDataIndex);
}

FVector AAIRToy::GetLaunchVelocity() const
{
    if (!GetOwnerCharacter()) return FVector();

    FRotator LaunchRotation = GetOwnerCharacter()->GetBaseAimRotation();

    FVector LaunchVelocity = LaunchRotation.Vector() * ThrowDistance;

    return LaunchVelocity;
}

void AAIRToy::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(AAIRToy, InHands);
    DOREPLIFETIME(AAIRToy, ToyDataIndex);
}

bool AAIRToy::CanUseItem() const
{
    return InHands;
}
