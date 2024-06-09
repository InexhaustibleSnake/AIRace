// This project is made for a test assignment

#include "Characters/AIRPlayerCharacter.h"

#include "Camera/CameraComponent.h"

#include "Components/AIRItemComponent.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"

AAIRPlayerCharacter::AAIRPlayerCharacter()
{
    MainCamera = CreateDefaultSubobject<UCameraComponent>("MainCamera");
    MainCamera->SetupAttachment(GetRootComponent());
    MainCamera->bUsePawnControlRotation = true;

    AIRItemComponent = CreateDefaultSubobject<UAIRItemComponent>("AIRItemComponent");

    GetMesh()->SetOwnerNoSee(true);
}

void AAIRPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
    {
        if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
                ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
        {
            Subsystem->AddMappingContext(DefaultMappingContext, 0);
        }
    }

    if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
    {
        EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
        EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

        EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAIRPlayerCharacter::Move);

        EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AAIRPlayerCharacter::Look);

        EnhancedInputComponent->BindAction(PrimaryUseAction, ETriggerEvent::Triggered, this, &AAIRPlayerCharacter::ItemPrimaryUse);
        EnhancedInputComponent->BindAction(SeconderyUseAction, ETriggerEvent::Triggered, this, &AAIRPlayerCharacter::ItemSeconderyUse);
    }
}

void AAIRPlayerCharacter::GetActorEyesViewPoint(FVector& OutLocation, FRotator& OutRotation) const
{
    if (!MainCamera)
    {
        OutLocation = GetActorLocation();
        OutRotation = GetControlRotation();

        return;
    }

    OutLocation = MainCamera->GetComponentLocation();
    OutRotation = GetBaseAimRotation();
}

void AAIRPlayerCharacter::Move(const FInputActionValue& Value)
{
    FVector2D MovementVector = Value.Get<FVector2D>();

    AddMovementInput(GetActorForwardVector(), MovementVector.X);
    AddMovementInput(GetActorRightVector(), MovementVector.Y);
}

void AAIRPlayerCharacter::Look(const FInputActionValue& Value)
{
    if (!GetWorld()) return;

    float DeltatTime = GetWorld()->GetDeltaSeconds();

    FVector2D LookVector = Value.Get<FVector2D>();

    AddControllerYawInput(LookVector.X * DeltatTime * LookInputScale.X);
    AddControllerPitchInput(LookVector.Y * DeltatTime * LookInputScale.Y);
}

void AAIRPlayerCharacter::ItemPrimaryUse()
{
    if (!AIRItemComponent) return;

    AIRItemComponent->PrimaryUse();
}

void AAIRPlayerCharacter::ItemSeconderyUse()
{
    if (!AIRItemComponent) return;

    AIRItemComponent->SeconderyUse();
}

USceneComponent* AAIRPlayerCharacter::GetItemAttachComponent() const
{
    return MainCamera;
}
