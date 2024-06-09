// This project is made for a test assignment

#include "Items/AIRBaseItem.h"

AAIRBaseItem::AAIRBaseItem()
{
    PrimaryActorTick.bCanEverTick = false;

    ItemMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("ItemMeshComponent");
    ItemMeshComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
    SetRootComponent(ItemMeshComponent);

    bReplicates = true;
}

void AAIRBaseItem::PrimaryUse() {}

void AAIRBaseItem::SeconderyUse() {}