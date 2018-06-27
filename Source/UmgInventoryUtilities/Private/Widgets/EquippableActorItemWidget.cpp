// Copyright 2018 iGotchaMedia Inc.  All rights reserved.

#include "EquippableActorItemWidget.h"
#include "TextBlock.h"
#include "Image.h"
#include "ComboBoxString.h"

void UEquippableActorItemWidget::NativeConstruct()
{
	Super::Construct();
	Super::NativeConstruct();
	SlotComboBox->OnSelectionChanged.AddDynamic(this, &UEquippableActorItemWidget::OnSlotSelectionChanged);
}

void UEquippableActorItemWidget::OnSlotSelectionChanged(FString Selection, ESelectInfo::Type SelectionType)
{
	auto DataWrapper = Cast<UEquippableActorItemDataWrapper>(ContainedObject);
	if (DataWrapper != nullptr)
	{
		DataWrapper->Data.ItemSlot = FName(*Selection);
	}
}

void UEquippableActorItemWidget::SetupWidget(FEquippableActorItem EquippableActorItem, TArray<FName> SlotOptions)
{
	auto DataWrapper = NewObject<UEquippableActorItemDataWrapper>();
	DataWrapper->Data = EquippableActorItem;
	ContainedObject = DataWrapper;
	if (ItemImage != nullptr)
	{
		ItemImage->SetBrushFromTexture(EquippableActorItem.ItemPreviewTexture);
	}
	if (ItemNameTextBlock != nullptr)
	{
		ItemNameTextBlock->SetText(FText::FromName(EquippableActorItem.ItemName));
	}
	for (auto SlotOption : SlotOptions)
	{
		SlotComboBox->AddOption(SlotOption.ToString());
	}
}


