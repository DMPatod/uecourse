// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CourseWidgetBase.h"
#include "ModerateLayoutBase.generated.h"

class UHSPBarBase;
class UImage;

UCLASS(Abstract)
class COURSE_API UModerateLayoutBase : public UCourseWidgetBase
{
public:
	UPROPERTY(BlueprintReadOnly, Category="Constituent Controls", meta=(BindWidget))
	TObjectPtr<UHSPBarBase> HSPBar = nullptr;

	UPROPERTY(BlueprintReadOnly, Category="Constituent Controls", meta=(BindWidget))
	TObjectPtr<UImage> HSPImage = nullptr;

private:
	GENERATED_BODY()
};
