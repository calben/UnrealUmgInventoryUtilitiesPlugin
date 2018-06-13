// Copyright 2018 iGotchaMedia Inc.  All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BastioniLABCharacters/Public/ClothedBastioniLabCharacter.h"
#include "MaterialEditorWidget.h"
#include "MaterialSelectionMenuWidget.generated.h"

UCLASS()
class UMaterialSelectionData : public UObject
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UMaterialInterface* Data;
};

USTRUCT(BlueprintType)
struct FMaterialAndIcon
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UMaterialInterface* Material;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UTexture2D* PreviewTexture;
};

USTRUCT(BlueprintType)
struct FMaterialSettings
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class UMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		FName SlotName;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		UMaterialInterface* Material;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		FMaterialParameterInfoValueCollection MaterialParamaterInfoValueCollection;

};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaterialConfirmed, FMaterialSettings, MaterialSettings);

/**
 *
 */
UCLASS()
class UMGINVENTORYUTILITIES_API UMaterialSelectionMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class USelectableObjectIconAndTextWidget> SelectableObjectIconAndTextWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class UMaterialEditorWidget> MaterialEditorWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FMaterialAndIcon> MaterialAndIcons;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class UMaterialSlotsOverviewWidget* MaterialSlotsOverviewWidget;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		FMaterialSettings MaterialSettings;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		FName SlotName;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class UMaterialInterface* SelectedMaterialInterface;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		FEquippableItem EquippableItem;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
		class UTextBlock* MenuTitleTextBlock;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
		class UMaterialSelectorWidget* MaterialSelectorWidget;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
		class UButton* ConfirmButton;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		FOnMaterialConfirmed OnMaterialConfirmedDelegate;

	void NativeConstruct() override;

	UFUNCTION(BlueprintCallable)
		void SetupWidget(FString FriendlySlotName, FName MaterialSlotName, FEquippableItem Item);

	UFUNCTION(BlueprintCallable)
		void OnMaterialSelected(const UObject* SelectedObject);

	UFUNCTION(BlueprintCallable)
		void OnChildMaterialEditorConfirmed(FMaterialParameterInfoValueCollection MaterialParameterInfoValueCollection);

	UFUNCTION(BlueprintCallable)
		void OnConfirm();

};
