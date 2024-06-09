// This project is made for a test assignment

#pragma once

#include "CoreMinimal.h"
#include "Items/AIRBaseItem.h"
#include "AIRToy.generated.h"

UCLASS()
class AIRACE_API AAIRToy : public AAIRBaseItem
{
    GENERATED_BODY()

public:
    virtual void PrimaryUse() override;
    virtual void SeconderyUse() override;

protected:
    void ThrowToy();
    void ReturnToy();

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

    UFUNCTION()
    void OnRep_InHands();
   
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Toy")
    float ThrowDistance = 2000.0f;

    FVector GetLaunchVelocity() const;

    UPROPERTY(ReplicatedUsing = OnRep_InHands)
    bool InHands = true;
};
