#include "HudCourseBase.h"

#include "CharacterCourseBase.h"
#include "LoggingDeclarations.h"
#include "MinimalLayoutBase.h"
#include "ModerateLayoutBase.h"
#include "OverloadLayoutBase.h"

void AHudCourseBase::SetCurrentViewMode(EHudViewMode NewViewMode)
{
	CurrentViewMode = NewViewMode;
	UpdateWidgets();
}

void AHudCourseBase::CycleToNextViewMode()
{
	++CurrentViewMode;
	UE_LOG(CourseLog, Warning, TEXT("CycleToNextViewMode %s"), *UEnum::GetValueAsString(CurrentViewMode));
	UpdateWidgets();
}

void AHudCourseBase::BeginPlay()
{
	Super::BeginPlay();

	World = GetWorld();
	checkf(World, TEXT("Failed to reference World."));

	checkf(MinimalLayoutClass, TEXT("Invalid MinimalLayoutClass reference."));
	checkf(ModerateLayoutClass, TEXT("Invalid ModerateLayoutClass reference."));
	checkf(OverloadLayoutClass, TEXT("Invalid OverloadLayoutClass reference."));

	MinimalLayoutWidget = CreateWidget<UMinimalLayoutBase>(World, MinimalLayoutClass);
	MinimalLayoutWidget->AddToViewport();
	MinimalLayoutWidget->SetVisibility(ESlateVisibility::Collapsed);

	ModerateLayoutWidget = CreateWidget<UModerateLayoutBase>(World, ModerateLayoutClass);
	ModerateLayoutWidget->AddToViewport();
	ModerateLayoutWidget->SetVisibility(ESlateVisibility::Collapsed);
	
	OverloadLayoutWidget = CreateWidget<UOverloadLayoutBase>(World, OverloadLayoutClass);
	OverloadLayoutWidget->AddToViewport();
	OverloadLayoutWidget->SetVisibility(ESlateVisibility::Collapsed);

	if (APlayerController* PlayerController = GetOwningPlayerController())
	{
		PlayerCharacter = Cast<ACharacterCourseBase>(PlayerController->GetPawn());
	}
	checkf(PlayerCharacter, TEXT("Unable to get a reference to the player character."));

	UpdateWidgets();
}

void AHudCourseBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	ClearAllHandlers();
	Super::EndPlay(EndPlayReason);
}

void AHudCourseBase::UpdateWidgets()
{
}

void AHudCourseBase::ClearAllHandlers()
{
	PlayerCharacter->OnHealthChanged.Clear();
	PlayerCharacter->OnStaminaChanged.Clear();
	PlayerCharacter->OnKeyWalletAction.Clear();
}
