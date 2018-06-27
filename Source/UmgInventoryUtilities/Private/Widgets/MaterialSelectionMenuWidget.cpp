// Copyright 2018 iGotchaMedia Inc.  All rights reserved.

#include "MaterialSelectionMenuWidget.h"

#include "SelectableObjectIconAndTextWidget.h"
#include "MaterialEditorWidget.h"
#include "TextBlock.h"
#include "Button.h"
#include "PanelWidget.h"
#include "WidgetTree.h"
#include "UmgInventoryUtilities.h"
#include "MaterialSelectorWidget.h"
#include "Runtime/Engine/Classes/Components/SkeletalMeshComponent.h"
#include "Runtime/Engine/Classes/Components/MeshComponent.h"
#include "Runtime/Engine/Classes/Materials/Material.h"
#include "Runtime/Engine/Classes/Materials/MaterialInstanceDynamic.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

void UMaterialSelectionMenuWidget::NativeConstruct()
{
	MaterialSelectorWidget->OnObjectSelectionChanged.AddDynamic(this, &UMaterialSelectionMenuWidget::OnMaterialSelected);
	ConfirmButton->OnReleased.AddDynamic(this, &UMaterialSelectionMenuWidget::OnConfirm);
}

void UMaterialSelectionMenuWidget::SetupWidget(FString FriendlySlotName, FName MaterialSlotName, FEquippableItem Item)
{
	SlotName = MaterialSlotName;
	MenuTitleTextBlock->SetText(FText::FromString(FriendlySlotName));
	EquippableItem = Item;
	if (SelectableObjectIconAndTextWidgetClass != nullptr)
	{
		if (EquippableItem.ItemMesh->GetName().Contains("hair"))
		{
			auto Path = FString::Printf(TEXT("MaterialInstanceConstant'/Game/Clothing/Materials/%s.%s'"), *Item.ItemMesh->GetName(), *Item.ItemMesh->GetName());
			UE_LOG(LogTemp, Warning, TEXT("Searching %s for material."), *Path);
			auto Material = Cast<UMaterialInterface>(StaticLoadObject(UMaterialInterface::StaticClass(), NULL, *(Path)));
			if (Material != nullptr)
			{
				auto Widget = WidgetTree->ConstructWidget<USelectableObjectIconAndTextWidget>(SelectableObjectIconAndTextWidgetClass);
				if (Widget != nullptr)
				{
					FSelectableObjectIconAndTextData Data;
					auto MaterialSelectionData = NewObject<UMaterialSelectionData>();
					MaterialSelectionData->Data = Material;
					Data.ContainedObject = MaterialSelectionData;
					Data.IconTexture = nullptr;
					Data.IconText = FText::FromString(Material->GetName());
					Widget->SetupSelectableObjectData(Data);
					UE_LOG(LogTemp, Warning, TEXT("Setup USelectableObjectIconAndTextWidget for %s."), *Data.IconText.ToString());
					MaterialSelectorWidget->AddSelectableObjectToWidget(Widget);
				}
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Failed to find material."));
			}
		}
		else
		{
			for (auto MaterialAndIcon : MaterialAndIcons)
			{
				auto Widget = WidgetTree->ConstructWidget<USelectableObjectIconAndTextWidget>(SelectableObjectIconAndTextWidgetClass);
				if (Widget != nullptr)
				{
					FSelectableObjectIconAndTextData Data;
					auto MaterialSelectionData = NewObject<UMaterialSelectionData>();
					MaterialSelectionData->Data = MaterialAndIcon.Material;
					Data.ContainedObject = MaterialSelectionData;
					Data.IconText = FText::FromString(MaterialAndIcon.Material->GetName());
					Data.IconTexture = MaterialAndIcon.PreviewTexture;
					Widget->SetupSelectableObjectData(Data);
					MaterialSelectorWidget->AddSelectableObjectToWidget(Widget);
				}
			}
		}
	}
}

void UMaterialSelectionMenuWidget::OnMaterialSelected(const UObject* SelectedObject)
{
	auto MaterialSelectionData = Cast<UMaterialSelectionData>(SelectedObject);
	if (MaterialSelectionData != nullptr)
	{
		if (MaterialSelectionData->Data != nullptr)
		{
			SelectedMaterialInterface = MaterialSelectionData->Data;
			auto MaterialInstanceDynamic = UMaterialInstanceDynamic::Create(MaterialSelectionData->Data, (UMeshComponent*)EquippableItem.ItemMeshComponent);
			if (MaterialInstanceDynamic != nullptr)
			{
				EquippableItem.ItemMeshComponent->SetMaterialByName(SlotName, MaterialInstanceDynamic);
				if (MaterialEditorWidgetClass != nullptr)
				{
					auto Widget = CreateWidget<UMaterialEditorWidget>(UGameplayStatics::GetPlayerController(GetWorld(), 0), MaterialEditorWidgetClass);
					if (Widget != nullptr)
					{
						Widget->SetupPanel(FText::FromString(SelectedMaterialInterface->GetName()), this, MaterialInstanceDynamic);
						Widget->OnMaterialParametersConfirmedDelegate.AddDynamic(this, &UMaterialSelectionMenuWidget::OnChildMaterialEditorConfirmed);
						Widget->AddToViewport();
					}
				}
			}
		}
	}
}

void UMaterialSelectionMenuWidget::OnChildMaterialEditorConfirmed(FMaterialParameterInfoValueCollection MaterialParameterInfoValueCollection)
{
	MaterialSettings.Mesh = Cast<UMeshComponent>(EquippableItem.ItemMesh);
	MaterialSettings.SlotName = SlotName;
	MaterialSettings.Material = SelectedMaterialInterface;
	MaterialSettings.MaterialParamaterInfoValueCollection = MaterialParameterInfoValueCollection;
}

void UMaterialSelectionMenuWidget::OnConfirm()
{
	if (OnMaterialConfirmedDelegate.IsBound())
	{
		OnMaterialConfirmedDelegate.Broadcast(MaterialSettings);
	}
	RemoveFromParent();
}
