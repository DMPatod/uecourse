#include "PlayerControllerCourseBase.h"

#include "InputAction.h"
#include "InputActionValue.h"
#include "CharacterCourseBase.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "HudCourseBase.h"

void APlayerControllerCourseBase::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);

	PlayerCharacter = Cast<ACharacterCourseBase>(aPawn);
	checkf(PlayerCharacter,
	       TEXT("APlayerControllerBase derived class should only possess ACharacterCourseBase derived pawns."));

	EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	checkf(EnhancedInputComponent, TEXT("Unable to get reference to the EnhancedInputComponent."));

	UEnhancedInputLocalPlayerSubsystem* InputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(
		GetLocalPlayer());
	checkf(InputSubsystem, TEXT("Unable to get reference to the EnhancedInputLocalPlayerSubsystem."));

	checkf(InputMappingContent, TEXT("InputMappingContext was not specified."));
	InputSubsystem->ClearAllMappings();
	InputSubsystem->AddMappingContext(InputMappingContent, 0);

	if (ActionMove)
	{
		EnhancedInputComponent->BindAction(ActionMove, ETriggerEvent::Triggered, this,
		                                   &APlayerControllerCourseBase::HandleMove);
	}

	if (ActionLook)
	{
		EnhancedInputComponent->BindAction(ActionLook, ETriggerEvent::Triggered, this,
		                                   &APlayerControllerCourseBase::HandleLook);
	}

	if (ActionJump)
	{
		EnhancedInputComponent->BindAction(ActionJump, ETriggerEvent::Triggered, this,
		                                   &APlayerControllerCourseBase::HandleJump);
	}

	if (ActionToggleSprint)
	{
		EnhancedInputComponent->BindAction(ActionToggleSprint, ETriggerEvent::Triggered, this,
		                                   &APlayerControllerCourseBase::HandleToggleSprint);
	}

	if (ActionToggleCrouch)
	{
		EnhancedInputComponent->BindAction(ActionToggleCrouch, ETriggerEvent::Triggered, this,
		                                   &APlayerControllerCourseBase::HandleToggleCrouch);
	}

	if (ActionCycleUIMode)
	{
		EnhancedInputComponent->BindAction(ActionCycleUIMode, ETriggerEvent::Triggered, this,
		                                   &APlayerControllerCourseBase::HandleCycleUIMode);
	}
}

void APlayerControllerCourseBase::OnUnPossess()
{
	EnhancedInputComponent->ClearActionBindings();

	Super::OnUnPossess();
}

void APlayerControllerCourseBase::HandleLook(const FInputActionValue& InputActionValue)
{
	const FVector2D LookAxisVector = InputActionValue.Get<FVector2D>();

	AddYawInput(LookAxisVector.X);
	AddPitchInput(LookAxisVector.Y);
}

void APlayerControllerCourseBase::HandleMove(const FInputActionValue& InputActionValue)
{
	const FVector2D MovementVector = InputActionValue.Get<FVector2D>();

	PlayerCharacter->AddMovementInput(PlayerCharacter->GetActorForwardVector(), MovementVector.Y);
	PlayerCharacter->AddMovementInput(PlayerCharacter->GetActorForwardVector(), MovementVector.X);
}

void APlayerControllerCourseBase::HandleJump()
{
	PlayerCharacter->UnCrouch();
	PlayerCharacter->Jump();
}

void APlayerControllerCourseBase::HandleToggleSprint()
{
	PlayerCharacter->ToggleSprinting();
}

void APlayerControllerCourseBase::HandleToggleCrouch()
{
	if (PlayerCharacter->IsCrouched())
	{
		PlayerCharacter->UnCrouch();
	}
	else
	{
		PlayerCharacter->Crouch();
	}
}

void APlayerControllerCourseBase::HandleCycleUIMode()
{
	if (PlayerHud)
	{
		PlayerHud->CycleToNextViewMode();
	}
}
