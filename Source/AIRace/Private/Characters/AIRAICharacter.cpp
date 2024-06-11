// This project is made for a test assignment

#include "Characters/AIRAICharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/TextRenderComponent.h"
#include "AI/AIRAIController.h"
#include "Net/UnrealNetwork.h"

AAIRAICharacter::AAIRAICharacter()
{
    BotNameText = CreateDefaultSubobject<UTextRenderComponent>("BotNameText");
    BotNameText->SetupAttachment(GetRootComponent());

    FVector BotNameTextLocation(0.0f, 0.0f, 100.0f);
    BotNameText->SetRelativeLocation(BotNameTextLocation);
    BotNameText->HorizontalAlignment = EHorizTextAligment::EHTA_Center;
    BotNameText->WorldSize = 10.0f;

    AIControllerClass = AAIRAIController::StaticClass();
}

void AAIRAICharacter::BeginPlay()
{
    Super::BeginPlay();

    if (RandomMovementSpeed)
    {
        SetMovementSpeed(FMath::RandRange(MovementSpeedRange.GetLowerBoundValue(), MovementSpeedRange.GetUpperBoundValue()));
    }

    SetBotNameText(FText::FromString(GetName()));
}

void AAIRAICharacter::SetMovementSpeed(float NewMovementSpeed)
{
    if (!GetCharacterMovement() || !HasAuthority()) return;

    GetCharacterMovement()->MaxWalkSpeed = NewMovementSpeed;
}

void AAIRAICharacter::SetBotNameText(const FText& NewText)
{
    if (!BotNameText) return;

    BotNameText->SetText(NewText);
}
