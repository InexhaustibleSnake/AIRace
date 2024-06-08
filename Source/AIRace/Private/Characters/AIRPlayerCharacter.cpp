// Fill out your copyright notice in the Description page of Project Settings.

#include "Characters/AIRPlayerCharacter.h"

#include "Camera/CameraComponent.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"

AAIRPlayerCharacter::AAIRPlayerCharacter()
{
    MainCamera = CreateDefaultSubobject<UCameraComponent>("MainCamera");
    MainCamera->SetupAttachment(GetRootComponent());
    MainCamera->bUsePawnControlRotation = true;

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
    }
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
