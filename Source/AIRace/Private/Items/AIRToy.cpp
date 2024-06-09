// This project is made for a test assignment

#include "Items/AIRToy.h"

#include "Characters/AIRPlayerCharacter.h"

#include "Net/UnrealNetwork.h"

void AAIRToy::PrimaryUse()
{
    if (!InHands) return;

    InHands = false;

    OnRep_InHands();
}

void AAIRToy::SeconderyUse()
{
    InHands = true;

    OnRep_InHands();
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
    if (!OwnerCharacter) return;

    const auto AttachComponent = OwnerCharacter->GetItemAttachComponent();

    AttachToOwner();
}

void AAIRToy::OnRep_InHands()
{
    InHands ? ReturnToy() : ThrowToy();
}

FVector AAIRToy::GetLaunchVelocity() const
{
    if (!GetOwner()) return FVector();

    FVector LaunchLocation;
    FRotator LaunchRotation;

    GetOwner()->GetActorEyesViewPoint(LaunchLocation, LaunchRotation);

    FVector LaunchVelocity = LaunchRotation.Vector() * ThrowDistance;

    return LaunchVelocity;
}

void AAIRToy::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(AAIRToy, InHands);
}