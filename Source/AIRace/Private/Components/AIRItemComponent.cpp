// This project is made for a test assignment

#include "Components/AIRItemComponent.h"
#include "Items/AIRBaseItem.h"
#include "Characters/AIRPlayerCharacter.h"

UAIRItemComponent::UAIRItemComponent()
{
    PrimaryComponentTick.bCanEverTick = false;

    SetIsReplicatedByDefault(true);
}

void UAIRItemComponent::BeginPlay()
{
    Super::BeginPlay();

    InitItems();
}

void UAIRItemComponent::PrimaryUse()
{
    if (!GetOwner()) return;

    if (!GetOwner()->HasAuthority())
    {
        ServerPrimaryUse();
        return;
    }

    if (!CurrentItem) return;

    CurrentItem->PrimaryUse();
}

void UAIRItemComponent::ServerPrimaryUse_Implementation()
{
    PrimaryUse();
}

void UAIRItemComponent::SeconderyUse()
{
    if (!GetOwner()) return;

    if (!GetOwner()->HasAuthority())
    {
        ServerSeconderyUse();
        return;
    }

    CurrentItem->SeconderyUse();
}

void UAIRItemComponent::ServerSeconderyUse_Implementation()
{
    SeconderyUse();
}

void UAIRItemComponent::InitItems()
{
    if (!GetWorld() || !GetOwner()->HasAuthority()) return;

    const auto SpawnedItem = GetWorld()->SpawnActor<AAIRBaseItem>(AvaibleItemClass);
    if (!SpawnedItem || !GetOwnerCharacter()) return;

    SpawnedItem->SetOwner(GetOwner());

    SpawnedItem->SetOwnerCharacter(Cast<AAIRPlayerCharacter>(GetOwner()));

    SpawnedItem->AttachToOwner();

    CurrentItem = SpawnedItem;
}

AAIRPlayerCharacter* UAIRItemComponent::GetOwnerCharacter() const
{
    return Cast<AAIRPlayerCharacter>(GetOwner());
}
