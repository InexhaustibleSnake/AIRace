// This project is made for a test assignment

#pragma once

#include "CoreMinimal.h"
#include "Characters/AIRBaseCharacter.h"
#include "AIRAICharacter.generated.h"

class UTextRenderComponent;

UCLASS()
class AIRACE_API AAIRAICharacter : public AAIRBaseCharacter
{
    GENERATED_BODY()

public:
    AAIRAICharacter();

    UFUNCTION(BlueprintCallable, Category = "Scores")
    int32 GetScores() const { return Score; }

    void AddScores(int32 Amount);

protected:
    virtual void BeginPlay() override;
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

    void SetMovementSpeed(float NewMovementSpeed);

    void SetBotNameText(const FText& NewText);

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    bool RandomMovementSpeed = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (EditCondition = "RandomMovementSpeed"))
    FFloatRange MovementSpeedRange = FFloatRange(400.0f, 700.0f);

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    UTextRenderComponent* BotNameText;

    UPROPERTY(Replicated)
    int32 Score = 0;
};
