// Copyright 2018 iGotchaMedia Inc.  All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "SelectableObjectBaseWidget.h"
#include "UmgInventoryUtilitiesTypes.h"

#include "SelectableMaterialItemWidget.generated.h"

/**
 *
 */
UCLASS()
class UMGINVENTORYUTILITIES_API USelectableMaterialItemWidget : public USelectableObjectBaseWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
		class UImage* ItemImage;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
		class UTextBlock* MaterialNameTextBlock;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
		class UTextBlock* MaterialTypeTextBlock;

	void NativeConstruct() override;

	UFUNCTION(BlueprintCallable)
		void SetupSelectableMaterialItemWidget(FInventoryMaterialItem MaterialItem);

};
