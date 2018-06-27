// Copyright 2018 iGotchaMedia Inc.  All rights reserved.

#include "SelectableMaterialItemWidget.h"
#include "UmgInventoryUtilities.h"
#include "TextBlock.h"
#include "Image.h"


void USelectableMaterialItemWidget::NativeConstruct()
{
	Super::Construct();
	Super::NativeConstruct();

}

void USelectableMaterialItemWidget::SetupSelectableMaterialItemWidget(FInventoryMaterialItem MaterialItem)
{
	//auto DataWrapper = NewObject<UEquippableItemDataWrapper>();
	//DataWrapper->Data = EquippableItem;
	//ContainedObject = DataWrapper;

	if (MaterialItem.PreviewImage != nullptr)
	{
		ItemImage->SetBrushFromTexture(MaterialItem.PreviewImage);
	}
	MaterialNameTextBlock->SetText(FText::FromName(MaterialItem.Name));
	MaterialTypeTextBlock->SetText(FText::FromName(MaterialItem.Type));
	UE_LOG(LogUmgInventoryUtilties, Log, TEXT("Setup selectable material widget %s"), *MaterialItem.Name.ToString());
}


