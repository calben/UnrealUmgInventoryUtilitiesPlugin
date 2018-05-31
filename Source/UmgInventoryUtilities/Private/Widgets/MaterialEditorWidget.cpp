// Copyright 2018 iGotchaMedia Inc.  All rights reserved.

#include "MaterialEditorWidget.h"

#include "Runtime/Engine/Classes/Materials/Material.h"
#include "Runtime/Engine/Classes/Materials/MaterialInstanceDynamic.h"
#include "WidgetTree.h"
#include "TextBlock.h"
#include "PanelWidget.h"
#include "Button.h"
#include "MaterialScalarParameterWidget.h"
#include "MaterialVectorParameterWidget.h"

void UMaterialEditorWidget::NativeConstruct()
{
	ConfirmButton->OnReleased.AddDynamic(this, &UMaterialEditorWidget::OnConfirmButton);
}

void UMaterialEditorWidget::SetupPanel(FText WidgetName, class UMaterialSelectionMenuWidget* Parent, UMaterialInstanceDynamic* Material)
{
	MaterialInstance = Material;
	TitleTextBlock->SetText(WidgetName);

	TArray<FMaterialParameterInfo> VectorParameters;
	TArray<FGuid> VectorParameterGuids;
	Material->GetAllVectorParameterInfo(VectorParameters, VectorParameterGuids);

	TArray<FMaterialParameterInfo> ScalarParameters;
	TArray<FGuid> ScalarParameterGuids;
	Material->GetAllScalarParameterInfo(ScalarParameters, ScalarParameterGuids);

	for (auto ExposedParameter : ExposedParameters)
	{
		for (int32 ParameterIdx = 0; ParameterIdx < VectorParameters.Num(); ParameterIdx++)
		{
			FName ParameterName = VectorParameters[ParameterIdx].Name;
			if (ParameterName.IsEqual(ExposedParameter.Name))
			{
				if (MaterialVectorParameterWidgetClass != nullptr)
				{
					auto Widget = WidgetTree->ConstructWidget<UMaterialVectorParameterWidget>(MaterialVectorParameterWidgetClass);
					if (Widget != nullptr)
					{
						ExposedMaterialWidgetsPanel->AddChild(Widget);
						Widget->SetupWidget(ExposedParameter.FriendlyName, VectorParameters[ParameterIdx], Material);
						MaterialVectorParameterWidgets.Add(Widget);
					}
				}
			}
		}
		for (int32 ParameterIdx = 0; ParameterIdx < ScalarParameters.Num(); ParameterIdx++)
		{
			FName ParameterName = ScalarParameters[ParameterIdx].Name;
			if (ParameterName.IsEqual(ExposedParameter.Name))
			{
				if (MaterialScalarParameterWidgetClass != nullptr)
				{
					auto Widget = WidgetTree->ConstructWidget<UMaterialScalarParameterWidget>(MaterialScalarParameterWidgetClass);
					if (Widget != nullptr)
					{
						ExposedMaterialWidgetsPanel->AddChild(Widget);
						Widget->SetupWidget(ExposedParameter.FriendlyName, ScalarParameters[ParameterIdx], Material);
						MaterialScalarParameterWidgets.Add(Widget);
					}
				}
			}
		}
	}
}

void UMaterialEditorWidget::OnConfirmButton()
{
	if (OnMaterialParametersConfirmedDelegate.IsBound())
	{
		FMaterialParameterInfoValueCollection MaterialParameterInfoValueCollection;
		for (auto MaterialScalarParameterWidget : MaterialScalarParameterWidgets)
		{
			MaterialParameterInfoValueCollection.MaterialScalarParameterInfoValues.Add(MaterialScalarParameterWidget->GetMaterialScalarParameterInfoValue());
		}
		for (auto MaterialVectorParameterWidget : MaterialVectorParameterWidgets)
		{
			MaterialParameterInfoValueCollection.MaterialVectorParameterInfoValues.Add(MaterialVectorParameterWidget->GetMaterialVectorParameterInfoValue());
		}
		OnMaterialParametersConfirmedDelegate.Broadcast(MaterialParameterInfoValueCollection);
	}
	if (bCloseOnConfirm)
		RemoveFromParent();
}
