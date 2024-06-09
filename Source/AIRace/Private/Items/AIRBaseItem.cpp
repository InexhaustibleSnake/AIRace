// This project is made for a test assignment

#include "Items/AIRBaseItem.h"
#include "Characters/AIRPlayerCharacter.h"
#include "Kismet/KismetMathLibrary.h"

AAIRBaseItem::AAIRBaseItem()
{
    PrimaryActorTick.bCanEverTick = false;

    ItemMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("ItemMeshComponent");
    ItemMeshComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
    ItemMeshComponent->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
    SetRootComponent(ItemMeshComponent);

    bReplicates = true;
    SetReplicateMovement(true);
}

void AAIRBaseItem::PrimaryUse() {}

void AAIRBaseItem::SeconderyUse() {}

void AAIRBaseItem::AttachToOwner()
{
    AttachToComponent(GetOwnerCharacter()->GetItemAttachComponent(), FAttachmentTransformRules::SnapToTargetNotIncludingScale);

    SetActorTransform(GetItemSpawnTransform());

    if (!ItemMeshComponent) return;

    ItemMeshComponent->SetSimulatePhysics(false);
}

void AAIRBaseItem::SetOwnerCharacter(TObjectPtr<AAIRPlayerCharacter> NewOwnerCharacrter)
{
    OwnerCharacter = NewOwnerCharacrter;

    SetOwner(OwnerCharacter);
}

TObjectPtr<AAIRPlayerCharacter> AAIRBaseItem::GetOwnerCharacter() const
{
    return OwnerCharacter;
}

FTransform AAIRBaseItem::GetItemSpawnTransform() const
{
    if (!GetOwner()) return FTransform();

    FVector SpawnLocation;
    FRotator SpawnRotation;

    GetOwner()->GetActorEyesViewPoint(SpawnLocation, SpawnRotation);

    FVector InverseLocation = UKismetMathLibrary::InverseTransformLocation(GetActorTransform(), SpawnLocation);

    FRotator InverseRotator = UKismetMathLibrary::InverseTransformRotation(GetActorTransform(), SpawnRotation);

    InverseLocation += InverseRotator.Vector() * ForwardSpawnOffset;
    InverseLocation.Z += VerticalSpawnOffset;

    SpawnLocation = UKismetMathLibrary::TransformLocation(GetActorTransform(), InverseLocation);

    FVector SpawnScale = GetOwner()->GetActorScale();

    return FTransform(SpawnRotation, SpawnLocation, SpawnScale);
}
