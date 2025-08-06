#include "CharacterCourseBase.h"

#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ACharacterCourseBase::ACharacterCourseBase()
{
	PrimaryActorTick.bCanEverTick = true;
	SetActorTickInterval(0.5f);
	SetActorTickEnabled(true);
}

void ACharacterCourseBase::AddMovementInput(FVector WorldDirection, float ScaleValue, bool bForce)
{
	if (bIsSprinting && CurrentStamina <= 0)
	{
		SetSprinting(false);
	}

	Super::AddMovementInput(WorldDirection, ScaleValue, bForce);

	if (bIsSprinting)
	{
		bHasSprinted = true;
	}
}

void ACharacterCourseBase::Jump()
{
	if (CurrentStamina - JumpStaminaCost >= 0.f)
	{
		UnCrouch();
		Super::Jump();
		bHasJumped = true;
	}
}

void ACharacterCourseBase::Crouch(bool bClientSimulation)
{
	SetSprinting(false);
	Super::Crouch(bClientSimulation);
}

int ACharacterCourseBase::GetHealth()
{
	return CurrentHealth;
}

void ACharacterCourseBase::UpdateHealth(int DeltaHealth)
{
	if (CurrentHealth <= 0.f)
	{
		return;
	}

	int OldValue = CurrentHealth;
	CurrentHealth += DeltaHealth;

	CurrentHealth = FMath::Clamp(CurrentHealth, -1.f, MaxHealth);

	if (OldValue != CurrentHealth)
	{
		OnHealthChanged.Broadcast(OldValue, CurrentHealth, MaxHealth);
	}

	if (CurrentHealth <= 0.f)
	{
		OnPlayerDied.Broadcast();
	}
}

void ACharacterCourseBase::SetMaxHealth(int NewMaxHealth)
{
	MaxHealth = NewMaxHealth;
}

float ACharacterCourseBase::GetStamina()
{
	return CurrentStamina;
}

float ACharacterCourseBase::GetStaminaRegenRate()
{
	return StaminaRegenRate;
}

void ACharacterCourseBase::SetStaminaRegenRate(float NewStaminaRegenRate)
{
	StaminaRegenRate = NewStaminaRegenRate;
}

void ACharacterCourseBase::AddKey(FString KeyToAdd)
{
	if (!KeyWallet.Contains(KeyToAdd))
	{
		KeyWallet.Add(KeyToAdd);
	}
}

void ACharacterCourseBase::RemoveKey(FString KeyToRemove)
{
	if (KeyWallet.Contains(KeyToRemove))
	{
		KeyWallet.Remove(KeyToRemove);
	}
}

bool ACharacterCourseBase::IsKeyOnWallet(FString Key)
{
	return KeyWallet.Contains(Key);
}

void ACharacterCourseBase::SetSprinting(bool IsSprinting)
{
	bIsSprinting = IsSprinting;

	GetCharacterMovement()->MaxWalkSpeed = bIsSprinting ? NormalMaxWalkSpeed : SprintingMaxWalkSpeed;
}

void ACharacterCourseBase::ToggleSprinting()
{
	SetSprinting(!bIsSprinting);
}

void ACharacterCourseBase::BroadcastCurrentStats()
{
	OnHealthChanged.Broadcast(CurrentHealth, CurrentHealth, MaxHealth);
	OnStaminaChanged.Broadcast(CurrentStamina, CurrentStamina, MaxStamina);

	FString AllKeys = FString();
	for (FString Key : KeyWallet)
	{
		AllKeys.Appendf(TEXT("%s,"), *Key);
	}

	OnKeyWalletAction.Broadcast(AllKeys, EPlayerKeyAction::CountKeys, true);
}

// Called when the game starts or when spawned
void ACharacterCourseBase::BeginPlay()
{
	Super::BeginPlay();
	if (GetMovementComponent())
	{
		GetMovementComponent()->GetNavAgentPropertiesRef().bCanCrouch = true;
	}
}

// Called every frame
void ACharacterCourseBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	float CurrentStaminaRegenRate = StaminaRegenRate;
	if (bHasJumped)
	{
		CurrentStaminaRegenRate = -JumpStaminaCost;
	}
	else if (bHasSprinted)
	{
		CurrentStaminaRegenRate = -SprintStaminaCost;
	}
	else if (bIsCrouched)
	{
		CurrentStaminaRegenRate = RestStaminaRegenRate;
	}

	const float OldStamina = CurrentStamina;

	CurrentStamina = FMath::Clamp(CurrentStamina + CurrentStaminaRegenRate, 0.f, MaxStamina);

	if (CurrentStamina != OldStamina)
	{
		OnStaminaChanged.Broadcast(OldStamina, CurrentStamina, MaxStamina);
	}

	bHasSprinted = false;
	bHasJumped = false;
}

// Called to bind functionality to input
void ACharacterCourseBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
