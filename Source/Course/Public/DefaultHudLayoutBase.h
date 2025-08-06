// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CourseWidgetBase.h"
#include "DefaultHudLayoutBase.generated.h"

class UHealthStaminaBarBase;
class UImage;

UCLASS(Abstract)
class COURSE_API UDefaultHudLayoutBase : public UCourseWidgetBase
{
public:
	UPROPERTY(BlueprintReadOnly, Category="Constituent Controls", meta=(BindWidget))
	TObjectPtr<UHealthStaminaBarBase> BaseBars = nullptr;

	UPROPERTY(BlueprintReadOnly, Category="Constituent Controls", meta=(BindWidget))
	TObjectPtr<UImage> Crosshair = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "Definitions", meta = (ClampMin = 0, UIMin = 0))
	float CrosshairSize = 32.f;

private:
	virtual void NativeConstruct() override;

	GENERATED_BODY()
};
