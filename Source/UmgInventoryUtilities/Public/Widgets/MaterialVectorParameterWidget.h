// Copyright 2018 iGotchaMedia Inc.  All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/Engine/Classes/Materials/Material.h"
#include "MaterialEditorWidget.h"

#include "MaterialVectorParameterWidget.generated.h"

/**
 *
 */
UCLASS()
class UMGINVENTORYUTILITIES_API UMaterialVectorParameterWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UTextBlock* NameTextBlock;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		FMaterialParameterInfo MaterialParamaterInfo;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class UMaterialInstanceDynamic* MaterialInstance;

	void NativeConstruct() override;

	UFUNCTION(BlueprintCallable)
		void SetupWidget(FMaterialParameterInfo Parameter, class UMaterialInstanceDynamic* Material);

	UFUNCTION(BlueprintCallable)
		void UpdateParameter(FLinearColor Value);

	UFUNCTION(BlueprintCallable)
		FMaterialVectorParameterInfoValue GetMaterialVectorParameterInfoValue();

};
