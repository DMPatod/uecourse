// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CourseWidgetBase.generated.h"

USTRUCT(BlueprintType)
struct FMyStruct
{
	UPROPERTY(EditAnywhere)
	uint16 Value = 0;

	GENERATED_BODY()
};

UCLASS(Abstract)
class COURSE_API UCourseWidgetBase : public UUserWidget
{
public:
#if WITH_EDITOR
	virtual const FText GetPaletteCategory() override;
#endif
	
	UPROPERTY(EditAnywhere)
	uint16 Value = 0;

private:
	GENERATED_BODY()
};
