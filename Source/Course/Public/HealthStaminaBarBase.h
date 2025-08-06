// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CourseWidgetBase.h"
#include "HealthStaminaBarBase.generated.h"

class UStatBarBase;

UCLASS(Abstract)
class COURSE_API UHealthStaminaBarBase : public UCourseWidgetBase
{
public:
	UPROPERTY(BlueprintReadOnly, Category = "Constituent Controls", meta = (BindWidget))
	TObjectPtr<UStatBarBase> HealthBar = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "Constituent Controls", meta = (BindWidget))
	TObjectPtr<UStatBarBase> StaminaBar = nullptr;

private:
	GENERATED_BODY()
};
