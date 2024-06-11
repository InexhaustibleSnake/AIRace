// This project is made for a test assignment

#pragma once

#include "CoreMinimal.h"
#include "Items/AIRBaseItem.h"
#include "AIRToy.generated.h"

class AAIRRaceGameMode;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnToyUsedSignature, AAIRToy*, InToy);

USTRUCT(BlueprintType)
struct FToyData
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Toy")
    UStaticMesh* ToyStaticMesh = nullptr;

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

    void ReturnToy();

    FOnToyUsedSignature OnToyUsed;

    UFUNCTION(BlueprintCallable)
    int32 GetToyValue() const { return ToyValue; }

    void SetCanUseToy(bool CanUse);

protected:
    virtual void BeginPlay() override;

    void SetToyData(int32 DataIndex);

    void ThrowToy();

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

    bool CanUseItem() const;

    UFUNCTION()
    void OnRep_InHands();

    UFUNCTION()
    void OnRep_ToyDataIndex();

    AAIRRaceGameMode* GetGameMode() const;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Toy")
    float ThrowDistance = 2000.0f;

    FVector GetLaunchVelocity() const;

    UPROPERTY(ReplicatedUsing = OnRep_InHands)
    bool InHands = true;

    bool CanUseToy = true;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Toy")
    TArray<FToyData> DefaultToyData;

    int32 ToyValue = 0;

    UPROPERTY(ReplicatedUsing = OnRep_ToyDataIndex)
    int32 ToyDataIndex = 0;
};
