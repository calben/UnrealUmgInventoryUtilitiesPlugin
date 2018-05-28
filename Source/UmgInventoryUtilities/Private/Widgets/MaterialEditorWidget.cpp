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

void UMaterialEditorWidget::SetupPanel(UMaterialInstanceDynamic* Material)
{
	TitleTextBlock->SetText(FText::FromString(Material->GetName()));

	TArray<FMaterialParameterInfo> VectorParameters;
	TArray<FGuid> VectorParameterGuids;
	Material->GetAllVectorParameterInfo(VectorParameters, VectorParameterGuids);
	for (int32 ParameterIdx = 0; ParameterIdx < VectorParameters.Num(); ParameterIdx++)
	{
		FName ParameterName = VectorParameters[ParameterIdx].Name;
		for (auto ExposedParameter : ExposedParameters)
		{
			if (ParameterName.IsEqual(ExposedParameter.Name))
			{
				if (MaterialVectorParameterWidgetClass != nullptr)
				{
					auto Widget = WidgetTree->ConstructWidget<UMaterialVectorParameterWidget>(MaterialVectorParameterWidgetClass);
					if (Widget != nullptr)
					{
						ExposedMaterialWidgetsPanel->AddChild(Widget);
						Widget->SetupWidget(VectorParameters[ParameterIdx], Material);
						MaterialVectorParameterWidgets.Add(Widget);
					}
				}
			}
		}
	}

	TArray<FMaterialParameterInfo> ScalarParameters;
	TArray<FGuid> ScalarParameterGuids;
	Material->GetAllScalarParameterInfo(ScalarParameters, ScalarParameterGuids);
	for (int32 ParameterIdx = 0; ParameterIdx < ScalarParameters.Num(); ParameterIdx++)
	{
		FName ParameterName = ScalarParameters[ParameterIdx].Name;
		for (auto ExposedParameter : ExposedParameters)
		{
			if (ParameterName.IsEqual(ExposedParameter.Name))
			{
				if (MaterialScalarParameterWidgetClass != nullptr)
				{
					auto Widget = WidgetTree->ConstructWidget<UMaterialScalarParameterWidget>(MaterialScalarParameterWidgetClass);
					if (Widget != nullptr)
					{
						ExposedMaterialWidgetsPanel->AddChild(Widget);
						Widget->SetupWidget(ScalarParameters[ParameterIdx], Material);
						MaterialScalarParameterWidgets.Add(Widget);
					}
				}
			}
		}
	}
}

void UMaterialEditorWidget::OnConfirmButton()
{
	if (OnMaterialConfirmed.IsBound())
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
		OnMaterialConfirmed.Broadcast(MaterialParameterInfoValueCollection);
	}
	if (bCloseOnConfirm)
		RemoveFromParent();
}
