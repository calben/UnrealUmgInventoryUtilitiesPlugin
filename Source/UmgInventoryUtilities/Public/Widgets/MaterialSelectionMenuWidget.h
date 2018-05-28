// Copyright 2018 iGotchaMedia Inc.  All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
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
		FName SlotName;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class UMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
		class UTextBlock* MenuTitleTextBlock;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
		class UMaterialSelectorWidget* MaterialSelectorWidget;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
		class UButton* ConfirmButton;

	void NativeConstruct() override;

	UFUNCTION(BlueprintCallable)
		void SetupWidget(FName MaterialSlotName, UMeshComponent* MeshComponent);

	UFUNCTION(BlueprintCallable)
		void OnMaterialSelected(const UObject* SelectedObject);

	UFUNCTION(BlueprintCallable)
		void OnConfirm();

};
