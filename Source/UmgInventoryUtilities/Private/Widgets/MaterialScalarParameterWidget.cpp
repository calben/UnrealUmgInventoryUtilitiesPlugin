// Copyright 2018 iGotchaMedia Inc.  All rights reserved.

#include "MaterialScalarParameterWidget.h"

#include "Runtime/Engine/Classes/Materials/Material.h"
#include "Runtime/Engine/Classes/Materials/MaterialInstanceDynamic.h"
#include "TextBlock.h"
#include "Slider.h"

void UMaterialScalarParameterWidget::NativeConstruct()
{
	ValueSlider->OnValueChanged.AddDynamic(this, &UMaterialScalarParameterWidget::UpdateParameter);
}

void UMaterialScalarParameterWidget::SetupWidget(FName WidgetName, FMaterialParameterInfo Parameter, UMaterialInstanceDynamic * Material)
{
	NameTextBlock->SetText(FText::FromName(WidgetName));
	MaterialInstance = Material;
	MaterialParamaterInfo = Parameter;
	float Value;
	Material->GetScalarParameterValue(Parameter, Value);
	ValueSlider->SetValue(Value);
}

void UMaterialScalarParameterWidget::UpdateParameter(float Value)
{
	if (MaterialInstance != nullptr)
	{
		MaterialInstance->SetScalarParameterValue(MaterialParamaterInfo.Name, Value);
	}
}

FMaterialScalarParameterInfoValue UMaterialScalarParameterWidget::GetMaterialScalarParameterInfoValue()
{
	FMaterialScalarParameterInfoValue Result;
	Result.ParameterInfo = MaterialParamaterInfo;
	if (MaterialInstance != nullptr)
		MaterialInstance->GetScalarParameterValue(MaterialParamaterInfo, Result.Value);
	return Result;
}
