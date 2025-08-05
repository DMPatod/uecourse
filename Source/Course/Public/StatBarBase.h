// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CourseWidgetBase.h"
#include "StatBarBase.generated.h"

class UVerticalBox;
class UHorizontalBox;
class UBorder;
class UTextBlock;

UCLASS(Abstract)
class COURSE_API UStatBarBase : public UCourseWidgetBase
{
public:
	UFUNCTION()
	void OnIntStatUpdated(int32 OldValue, int32 NewValue, int32 MaxValue);

	UFUNCTION()
	void OnFloatStatUpdated(float OldValue, float NewValue, float MaxValue);

#if WITH_EDITOR
	virtual void OnDesignerChanged(const FDesignerChangedEventArgs& EventArgs) override;
	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

protected:
	virtual void NativeOnInitialized() override;

	UPROPERTY(BlueprintReadOnly, Category="Constituent Controls", meta=(BindWidget))
	TObjectPtr<UVerticalBox> MainBox = nullptr;

	UPROPERTY(BlueprintReadOnly, Category="Constituent Controls", meta=(BindWidget))
	TObjectPtr<UTextBlock> NameText = nullptr;

	UPROPERTY(BlueprintReadOnly, Category="Constituent Controls", meta=(BindWidget))
	TObjectPtr<UTextBlock> ValueText = nullptr;

	UPROPERTY(BlueprintReadOnly, Category="Constituent Controls", meta=(BindWidget))
	TObjectPtr<UHorizontalBox> PercentBars = nullptr;

	UPROPERTY(BlueprintReadOnly, Category="Constituent Controls", meta=(BindWidget))
	TObjectPtr<UBorder> Marker_Start = nullptr;

	UPROPERTY(BlueprintReadOnly, Category="Constituent Controls", meta=(BindWidget))
	TObjectPtr<UBorder> PercentBar_Filled = nullptr;

	UPROPERTY(BlueprintReadOnly, Category="Constituent Controls", meta=(BindWidget))
	TObjectPtr<UBorder> PercentBar_Empty = nullptr;

	UPROPERTY(BlueprintReadOnly, Category="Constituent Controls", meta=(BindWidget))
	TObjectPtr<UBorder> Marker_End = nullptr;

private:
	UPROPERTY(EditAnywhere, Category="Stat Bar")
	FLinearColor BarForegroundColor = FLinearColor(1.0f, 1.0f, 1.0f, 1.0f);

	UPROPERTY(EditAnywhere, Category="Stat Bar")
	FLinearColor BarBackgroundColor = FLinearColor(0.045f, 0.067f, 0.04f, 0.3f);

	UPROPERTY(EditAnywhere, Category="Stat Bar")
	FLinearColor MakerColor = FLinearColor(1.0f, 1.0f, 1.0f, 0.3f);

	UPROPERTY(EditAnywhere, Category="Stat Bar")
	bool IsFullSize = true;

	UPROPERTY(EditAnywhere, Category="Stat Bar|Testing", meta=(MaxLength=10))
	FString NameValue = "Example";

	UPROPERTY(EditAnywhere, Category="Stat Bar|Testing",
		meta=(ClampMin=0, UIMin =0, ClampMax=1, UIMax=1, Units="Percent"))
	float CurrentPercentage = 0.f;

	UPROPERTY(EditAnywhere, Category="Stat Bar|Testing", meta=(ClampMin=0, UIMin=0))
	float CurrentValue = 100.f;

	FText CurrentValueText;

	void ProcessCurrentValueText();

	void UpdatedWidget();

	GENERATED_BODY()
};
