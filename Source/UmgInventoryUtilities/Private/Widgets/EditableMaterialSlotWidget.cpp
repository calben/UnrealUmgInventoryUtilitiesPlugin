// Copyright 2018 iGotchaMedia Inc.  All rights reserved.

#include "EditableMaterialSlotWidget.h"

#include "Button.h"
#include "TextBlock.h"
#include "WidgetTree.h"
#include "MaterialSelectionMenuWidget.h"
#include "MaterialSlotsOverviewWidget.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/Components/MeshComponent.h"

void UEditableMaterialSlotWidget::NativeConstruct()
{
	EditButton->OnReleased.AddDynamic(this, &UEditableMaterialSlotWidget::OnEdit);
}

void UEditableMaterialSlotWidget::SetupWidget(UMaterialSlotsOverviewWidget* Parent, FName Name, FEquippableItem Item)
{
	MaterialSlotsOverviewWidget = Parent;
	EquippableItem = Item;
	SlotName = Name;
	FriendlySlotName = Name.ToString().Replace(TEXT("_"), TEXT(" "));
	NameTextBlock->SetText(FText::FromString(FriendlySlotName));
}

void UEditableMaterialSlotWidget::OnEdit()
{
	if (MaterialSelectionMenuWidgetClass != nullptr)
	{
		auto Widget = CreateWidget<UMaterialSelectionMenuWidget>(UGameplayStatics::GetPlayerController(GetWorld(), 0), MaterialSelectionMenuWidgetClass);
		if (Widget != nullptr)
		{
			Widget->SetupWidget(FriendlySlotName, SlotName, EquippableItem);
			Widget->OnMaterialConfirmedDelegate.AddDynamic(MaterialSlotsOverviewWidget, &UMaterialSlotsOverviewWidget::OnChildMaterialSelectionMenuWidgetConfirmed);
			Widget->AddToViewport();
		}
	}
}
