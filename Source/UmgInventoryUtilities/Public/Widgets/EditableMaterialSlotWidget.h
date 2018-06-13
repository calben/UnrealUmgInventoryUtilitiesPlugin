// Copyright 2018 iGotchaMedia Inc.  All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BastioniLABCharacters/Public/ClothedBastioniLabCharacter.h"
#include "EditableMaterialSlotWidget.generated.h"

/**
 *
 */
UCLASS()
class UMGINVENTORYUTILITIES_API UEditableMaterialSlotWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		FEquippableItem EquippableItem;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class UMaterialSlotsOverviewWidget* MaterialSlotsOverviewWidget;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		FName SlotName;

	FString FriendlySlotName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class UMaterialSelectionMenuWidget> MaterialSelectionMenuWidgetClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
		class UTextBlock* NameTextBlock;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
		class UButton* EditButton;

	void NativeConstruct() override;

	UFUNCTION(BlueprintCallable)
		void SetupWidget(UMaterialSlotsOverviewWidget* Parent, FName Name, FEquippableItem Item);

	UFUNCTION(BlueprintCallable)
		void OnEdit();

};
