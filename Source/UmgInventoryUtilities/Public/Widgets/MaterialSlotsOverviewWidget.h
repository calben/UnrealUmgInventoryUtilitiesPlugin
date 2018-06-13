// Copyright 2018 iGotchaMedia Inc.  All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MaterialEditorWidget.h"
#include "BastioniLABCharacters/Public/ClothedBastioniLabCharacter.h"
#include "MaterialSelectionMenuWidget.h"
#include "MaterialSlotsOverviewWidget.generated.h"

USTRUCT(BlueprintType)
struct FItemMaterialInformation
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		TMap<FName, FMaterialSettings> SlotToMaterialParameterInfoValueCollection;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnItemMaterialInformationConfirmed, FItemMaterialInformation, ItemMaterialInformation);


/**
 *
 */
UCLASS()
class UMGINVENTORYUTILITIES_API UMaterialSlotsOverviewWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class UEditableMaterialSlotWidget> EditableMaterialSlotWidgetClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		FItemMaterialInformation ItemMaterialInformation;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		FEquippableItem EquippableItem;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
		class UTextBlock* MenuTitleTextBlock;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
		class UPanelWidget* EditableMaterialSlotsPanelWidget;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
		class UButton* ConfirmButton;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		FOnItemMaterialInformationConfirmed OnItemMaterialInformationConfirmedDelegate;

	void NativeConstruct() override;

	UFUNCTION(BlueprintCallable)
		void SetupWidget(FText WidgetName, FEquippableItem Item);

	UFUNCTION(BlueprintCallable)
		void OnConfirmButton();

	UFUNCTION(BlueprintCallable)
		void OnChildMaterialSelectionMenuWidgetConfirmed(FMaterialSettings MaterialSettings);

};
