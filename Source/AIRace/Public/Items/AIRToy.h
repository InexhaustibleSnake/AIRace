// This project is made for a test assignment

#pragma once

#include "CoreMinimal.h"
#include "Items/AIRBaseItem.h"
#include "AIRToy.generated.h"

USTRUCT(BlueprintType)
struct FToyData
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Toy")
    UStaticMesh* ToyStaticMesh;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Toy", meta = (ClampMin = "0"))
    int32 Value = 1;
};

UCLASS()
class AIRACE_API AAIRToy : public AAIRBaseItem
{
    GENERATED_BODY()

public:
    virtual void PrimaryUse() override;
    virtual void SeconderyUse() override;

protected:
    void SetToyData(int32 DataIndex);

    void ThrowToy();
    void ReturnToy();

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

    bool CanUseItem() const;

    UFUNCTION()
    void OnRep_InHands();

    UFUNCTION()
    void OnRep_ToyDataIndex();

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Toy")
    float ThrowDistance = 2000.0f;

    FVector GetLaunchVelocity() const;

    UPROPERTY(ReplicatedUsing = OnRep_InHands)
    bool InHands = true;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Toy")
    TArray<FToyData> DefaultToyData;

    int32 ToyValue = 0;

    UPROPERTY(ReplicatedUsing = OnRep_ToyDataIndex)
    int32 ToyDataIndex = 0;
};
