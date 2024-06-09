// This project is made for a test assignment

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AIRItemComponent.generated.h"

class AAIRBaseItem;
class AAIRPlayerCharacter;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class AIRACE_API UAIRItemComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UAIRItemComponent();

    virtual void PrimaryUse();
    virtual void SeconderyUse();

protected:
    virtual void BeginPlay() override;

protected:
    void InitItems();

    UFUNCTION(Server, Unreliable)
    void ServerPrimaryUse();
    void ServerPrimaryUse_Implementation();

    UFUNCTION(Server, Unreliable)
    void ServerSeconderyUse();
    void ServerSeconderyUse_Implementation();

    AAIRPlayerCharacter* GetOwnerCharacter() const;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Items")
    TSubclassOf<AAIRBaseItem> AvaibleItemClass;

    UPROPERTY(BlueprintReadOnly, Category = "Items")
    TObjectPtr<AAIRBaseItem> CurrentItem;
};
