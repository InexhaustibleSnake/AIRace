// This project is made for a test assignment

#include "Components/AIRItemComponent.h"
#include "Items/AIRBaseItem.h"
#include "Characters/AIRPlayerCharacter.h"

UAIRItemComponent::UAIRItemComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UAIRItemComponent::BeginPlay()
{
    Super::BeginPlay();

    if (GetOwner() || GetOwner()->HasAuthority())
    {
        InitItems();
    }
}

void UAIRItemComponent::PrimaryUse()
{
    if (!CurrentItem) return;

    CurrentItem->PrimaryUse();
}

void UAIRItemComponent::SeconderyUse()
{
    if (!CurrentItem) return;

    CurrentItem->SeconderyUse();
}

void UAIRItemComponent::InitItems()
{
    if (!GetWorld()) return;

    const auto SpawnedItem = GetWorld()->SpawnActor<AAIRBaseItem>(AvaibleItemClass);
    if (!SpawnedItem || !GetOwnerCharacter()) return;

    SpawnedItem->SetOwner(GetOwner());

    SpawnedItem->AttachToComponent(GetOwnerCharacter()->GetItemAttachComponent(), FAttachmentTransformRules::SnapToTargetNotIncludingScale);

    SpawnedItem->SetActorTransform(GetItemSpawnTransform());
}

FTransform UAIRItemComponent::GetItemSpawnTransform() const
{
    if (!GetOwner()) return FTransform();

    FVector SpawnLocation;
    FRotator SpawnRotation;

    GetOwner()->GetActorEyesViewPoint(SpawnLocation, SpawnRotation);

    SpawnLocation += (SpawnRotation.Vector() * ForwardSpawnOffset);
    SpawnLocation.Z += VerticalSpawnOffset;

    FVector SpawnScale = GetOwner()->GetActorScale();

    return FTransform(SpawnRotation, SpawnLocation, SpawnScale);
}

AAIRPlayerCharacter* UAIRItemComponent::GetOwnerCharacter() const
{
    return Cast<AAIRPlayerCharacter>(GetOwner());
}
