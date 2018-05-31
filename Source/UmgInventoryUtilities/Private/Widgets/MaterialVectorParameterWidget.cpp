// Copyright 2018 iGotchaMedia Inc.  All rights reserved.

#include "MaterialVectorParameterWidget.h"

#include "Runtime/Engine/Classes/Materials/Material.h"
#include "Runtime/Engine/Classes/Materials/MaterialInstanceDynamic.h"
#include "TextBlock.h"
#include "Slider.h"

void UMaterialVectorParameterWidget::NativeConstruct()
{
}

void UMaterialVectorParameterWidget::SetupWidget(FName WidgetName, FMaterialParameterInfo Parameter, UMaterialInstanceDynamic * Material)
{
	NameTextBlock->SetText(FText::FromName(WidgetName));
	MaterialInstance = Material;
	MaterialParamaterInfo = Parameter;
	UpdateColorWidget();
}

void UMaterialVectorParameterWidget::UpdateParameter(FLinearColor Value)
{
	if (MaterialInstance != nullptr)
	{
		MaterialInstance->SetVectorParameterValue(MaterialParamaterInfo.Name, Value);
	}
}

FMaterialVectorParameterInfoValue UMaterialVectorParameterWidget::GetMaterialVectorParameterInfoValue()
{
	FMaterialVectorParameterInfoValue Result;
	Result.ParameterInfo = MaterialParamaterInfo;
	if (MaterialInstance != nullptr)
		MaterialInstance->GetVectorParameterValue(MaterialParamaterInfo, Result.Value);
	return Result;
}

