// This project is made for a test assignment

#pragma once

#include "CoreMinimal.h"
#include "Characters/AIRBaseCharacter.h"
#include "AIRPlayerCharacter.generated.h"

class UCameraComponent;
class UAIRItemComponent;

class UInputAction;
class UInputMappingContext;
struct FInputActionValue;

UCLASS()
class AIRACE_API AAIRPlayerCharacter : public AAIRBaseCharacter
{
    GENERATED_BODY()

public:
    AAIRPlayerCharacter();

    USceneComponent* GetItemAttachComponent() const;

protected:
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    virtual void GetActorEyesViewPoint(FVector& OutLocation, FRotator& OutRotation) const override;

    void Move(const FInputActionValue& Value);
    void Look(const FInputActionValue& Value);

    virtual void ItemPrimaryUse();
    virtual void ItemSeconderyUse();

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
    TObjectPtr<UCameraComponent> MainCamera;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
    TObjectPtr<UAIRItemComponent> AIRItemComponent;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Input")
    UInputMappingContext* DefaultMappingContext;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Input")
    UInputAction* JumpAction;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Input")
    UInputAction* MoveAction;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Input")
    UInputAction* LookAction;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Input")
    UInputAction* PrimaryUseAction;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Input")
    UInputAction* SeconderyUseAction;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Input")
    FVector2D LookInputScale = FVector2D(90.0f, 90.0f);
};
