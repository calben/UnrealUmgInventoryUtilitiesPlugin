// Copyright 2018 iGotchaMedia Inc.  All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "SelectableObjectBaseWidget.h"
#include "ClothedBastioniLabCharacter.h"

#include "EquippableActorItemWidget.generated.h"

UCLASS(Blueprintable)
class UMGINVENTORYUTILITIES_API UEquippableActorItemDataWrapper : public UObject
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FEquippableActorItem Data;
};

/**
 *
 */
UCLASS()
class UMGINVENTORYUTILITIES_API UEquippableActorItemWidget : public USelectableObjectBaseWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
		class UImage* ItemImage;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
		class UTextBlock* ItemNameTextBlock;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
		class UComboBoxString* SlotComboBox;

	void NativeConstruct() override;

	UFUNCTION(BlueprintCallable)
		void OnSlotSelectionChanged(FString Selection, ESelectInfo::Type SelectionType);

	UFUNCTION(BlueprintCallable)
		void SetupWidget(FEquippableActorItem EquippableActorItem, TArray<FName> SlotOptions);

};
