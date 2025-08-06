#include "DebugHudLayoutBase.h"
#include <Components/CanvasPanelSlot.h>
#include <Components/Image.h>
#include "HealthStaminaBarBase.h"
#include "StatBarBase.h"

void UDebugHudLayoutBase::NativeConstruct()
{
	Super::NativeConstruct();
	if (BaseBars)
	{
		BaseBars->HealthBar->Detailed = true;
		BaseBars->StaminaBar->Detailed = true;
	}
	if (Crosshair)
	{
		if (UCanvasPanelSlot* Canvas = Cast<UCanvasPanelSlot>(Crosshair->Slot))
		{
			FAnchors Anchors;
			Anchors.Minimum = FVector2D(0.5, 0.5);
			Anchors.Maximum = FVector2D(0.5, 0.5);
			Canvas->SetAnchors(Anchors);
			Canvas->SetSize(FVector2D(CrosshairSize, CrosshairSize));
			Canvas->SetAlignment(FVector2D(0.5, 0.5));
		}
	}
}
