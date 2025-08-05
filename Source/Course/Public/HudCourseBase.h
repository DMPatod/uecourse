#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "HudCourseBase.generated.h"

class ACharacterCourseBase;
class UMinimalLayoutBase;
class UModerateLayoutBase;
class UOverloadLayoutBase;

UENUM(BlueprintType)
enum class EHudViewMode: uint8
{
	CleanAndPristine UMETA(ToolTip=""),
	Minimal UMETA(ToolTip=""),
	Moderate UMETA(ToolTip=""),
	SensoryOverload UMETA(ToolTip="")
};

inline EHudViewMode& operator++(EHudViewMode& ViewMode)
{
	if (ViewMode == EHudViewMode::SensoryOverload)
		ViewMode = EHudViewMode::CleanAndPristine;
	else
		ViewMode = static_cast<EHudViewMode>(static_cast<int>(ViewMode) + 1);

	return ViewMode;
}

inline EHudViewMode& operator--(EHudViewMode& ViewMode)
{
	if (ViewMode == EHudViewMode::CleanAndPristine)
		ViewMode = EHudViewMode::SensoryOverload;
	else
		ViewMode = static_cast<EHudViewMode>(static_cast<int>(ViewMode) - 1);
	return ViewMode;
}

UCLASS(Abstract)
class COURSE_API AHudCourseBase : public AHUD
{
public:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UMinimalLayoutBase> MinimalLayoutClass = nullptr;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UModerateLayoutBase> ModerateLayoutClass = nullptr;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UOverloadLayoutBase> OverloadLayoutClass = nullptr;
	
	UFUNCTION(BlueprintCallable)
	void SetCurrentViewMode(EHudViewMode NewViewMode);

	UFUNCTION(BlueprintCallable)
	void CycleToNextViewMode();

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	UPROPERTY(EditAnywhere)
	EHudViewMode CurrentViewMode = EHudViewMode::Moderate;

	UPROPERTY()
	TObjectPtr<UWorld> World = nullptr;

	UPROPERTY()
	TObjectPtr<UMinimalLayoutBase>  MinimalLayoutWidget  = nullptr;
	
	UPROPERTY()
	TObjectPtr<UModerateLayoutBase> ModerateLayoutWidget = nullptr;
	
	UPROPERTY()
	TObjectPtr<UOverloadLayoutBase> OverloadLayoutWidget = nullptr;

	UPROPERTY()
	TObjectPtr<ACharacterCourseBase> PlayerCharacter;

	void UpdateWidgets();
	void ClearAllHandlers();

	GENERATED_BODY()
};
