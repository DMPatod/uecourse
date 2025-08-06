#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "DefaultHubBase.generated.h"

class ACharacterCourseBase;
class UDefaultHudLayoutBase;
class UDebugHudLayoutBase;

UENUM(BlueprintType)
enum class EHudViewMode : uint8
{
	Clean UMETA(ToolTip = "Nothing to show on UI."),
	Default UMETA(ToolTip = "Default HUD."),
	Debug UMETA(ToolTip = "Show every information.")
};

inline EHudViewMode& operator++(EHudViewMode& ViewMode)
{
	if (ViewMode == EHudViewMode::Debug)
		ViewMode = EHudViewMode::Clean;
	else
		ViewMode = static_cast<EHudViewMode>(static_cast<int>(ViewMode) + 1);

	return ViewMode;
}

inline EHudViewMode& operator--(EHudViewMode& ViewMode)
{
	if (ViewMode == EHudViewMode::Clean)
		ViewMode = EHudViewMode::Debug;
	else
		ViewMode = static_cast<EHudViewMode>(static_cast<int>(ViewMode) - 1);
	return ViewMode;
}

UCLASS(Abstract)
class COURSE_API ADefaultHubBase : public AHUD
{
public:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UDefaultHudLayoutBase> DefaultLayoutClass = nullptr;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UDebugHudLayoutBase> DebugLayoutClass = nullptr;

	UFUNCTION(BlueprintCallable)
	void SetCurrentViewMode(EHudViewMode NewViewMode);

	UFUNCTION(BlueprintCallable)
	void CycleToNextViewMode();

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	UPROPERTY(EditAnywhere)
	EHudViewMode CurrentViewMode = EHudViewMode::Default;

	UPROPERTY()
	TObjectPtr<UWorld> World = nullptr;

	UPROPERTY()
	TObjectPtr<UDefaultHudLayoutBase>  DefaultLayoutWidget = nullptr;

	UPROPERTY()
	TObjectPtr<UDebugHudLayoutBase> DebugLayoutWidget = nullptr;

	UPROPERTY()
	TObjectPtr<ACharacterCourseBase> PlayerCharacter;

	void UpdateWidgets();
	void ClearAllHandlers();

	GENERATED_BODY()
};
