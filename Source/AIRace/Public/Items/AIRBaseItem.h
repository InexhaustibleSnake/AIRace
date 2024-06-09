// This project is made for a test assignment

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AIRBaseItem.generated.h"

class AAIRPlayerCharacter;

UCLASS()
class AIRACE_API AAIRBaseItem : public AActor
{
    GENERATED_BODY()

public:
    AAIRBaseItem();

    virtual void PrimaryUse();
    virtual void SeconderyUse();

    void AttachToOwner();

    void SetOwnerCharacter(TObjectPtr<AAIRPlayerCharacter> NewOwnerCharacrter);

    TObjectPtr<AAIRPlayerCharacter> GetOwnerCharacter() const;

protected:
    FTransform GetItemSpawnTransform() const;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
    TObjectPtr<UStaticMeshComponent> ItemMeshComponent;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Items")
    float ForwardSpawnOffset = 50.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Items")
    float VerticalSpawnOffset = -25.0f;

    UPROPERTY()
    TObjectPtr<AAIRPlayerCharacter> OwnerCharacter;
};
