// This project is made for a test assignment

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AIRBaseItem.generated.h"

UCLASS()
class AIRACE_API AAIRBaseItem : public AActor
{
    GENERATED_BODY()

public:
    AAIRBaseItem();

    virtual void PrimaryUse();
    virtual void SeconderyUse();

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
    TObjectPtr<UStaticMeshComponent> ItemMeshComponent;
};
