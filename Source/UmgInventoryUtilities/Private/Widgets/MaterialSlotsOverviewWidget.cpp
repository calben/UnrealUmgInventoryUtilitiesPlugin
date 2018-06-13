// Copyright 2018 iGotchaMedia Inc.  All rights reserved.

#include "MaterialSlotsOverviewWidget.h"

#include "WidgetTree.h"
#include "Button.h"
#include "PanelWidget.h"
#include "EditableMaterialSlotWidget.h"
#include "Runtime/Engine/Classes/Components/MeshComponent.h"

void UMaterialSlotsOverviewWidget::NativeConstruct()
{
	ConfirmButton->OnReleased.AddDynamic(this, &UMaterialSlotsOverviewWidget::OnConfirmButton);
}

void UMaterialSlotsOverviewWidget::SetupWidget(FText WidgetName, FEquippableItem Item)
{
	MenuTitleTextBlock->SetText(WidgetName);
	EquippableItem = Item;
	for (auto Name : EquippableItem.ItemMeshComponent->GetMaterialSlotNames())
	{
		if (EditableMaterialSlotWidgetClass != nullptr)
		{
			auto Widget = WidgetTree->ConstructWidget<UEditableMaterialSlotWidget>(EditableMaterialSlotWidgetClass, Name);
			if (Widget != nullptr)
			{
				Widget->SetupWidget(this, Name, EquippableItem);
				EditableMaterialSlotsPanelWidget->AddChild(Widget);
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("No valid EditableMaterialSlotWidgetClass."));
		}
	}
}

void UMaterialSlotsOverviewWidget::OnConfirmButton()
{
	if (OnItemMaterialInformationConfirmedDelegate.IsBound())
	{
		OnItemMaterialInformationConfirmedDelegate.Broadcast(ItemMaterialInformation);
	}
	RemoveFromParent();
}

void UMaterialSlotsOverviewWidget::OnChildMaterialSelectionMenuWidgetConfirmed(FMaterialSettings MaterialSettings)
{
	ItemMaterialInformation.SlotToMaterialParameterInfoValueCollection.Add(MaterialSettings.SlotName, MaterialSettings);
}
