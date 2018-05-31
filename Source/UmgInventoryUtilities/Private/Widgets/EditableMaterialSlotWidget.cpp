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

void UEditableMaterialSlotWidget::SetupWidget(UMaterialSlotsOverviewWidget* Parent, FName Name, UMeshComponent* MeshComponent)
{
	MaterialSlotsOverviewWidget = Parent;
	Mesh = MeshComponent;
	SlotName = Name;
	NameTextBlock->SetText(FText::FromName(Name));
}

void UEditableMaterialSlotWidget::OnEdit()
{
	if (MaterialSelectionMenuWidgetClass != nullptr)
	{
		auto Widget = CreateWidget<UMaterialSelectionMenuWidget>(UGameplayStatics::GetPlayerController(GetWorld(), 0), MaterialSelectionMenuWidgetClass);
		if (Widget != nullptr)
		{
			Widget->SetupWidget(SlotName, Mesh);
			Widget->OnMaterialConfirmedDelegate.AddDynamic(MaterialSlotsOverviewWidget, &UMaterialSlotsOverviewWidget::OnChildMaterialSelectionMenuWidgetConfirmed);
			Widget->AddToViewport();
		}
	}
}
