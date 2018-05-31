// Copyright 2018 iGotchaMedia Inc.  All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/Engine/Classes/Materials/Material.h"

#include "MaterialEditorWidget.generated.h"

USTRUCT(BlueprintType)
struct FInventoryExposedMaterialParameter
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName FriendlyName;
};

// TODO move these to base types file
USTRUCT(BlueprintType)
struct FMaterialVectorParameterInfoValue
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		FMaterialParameterInfo ParameterInfo;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		FLinearColor Value;
};

USTRUCT(BlueprintType)
struct FMaterialScalarParameterInfoValue
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		FMaterialParameterInfo ParameterInfo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Value;
};

USTRUCT(BlueprintType)
struct FMaterialParameterInfoValueCollection
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FMaterialScalarParameterInfoValue> MaterialScalarParameterInfoValues;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FMaterialVectorParameterInfoValue> MaterialVectorParameterInfoValues;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaterialParametersConfirmed, FMaterialParameterInfoValueCollection, MaterialParameterInfoValueCollection);

/**
 *
 */
UCLASS()
class UMGINVENTORYUTILITIES_API UMaterialEditorWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FInventoryExposedMaterialParameter> ExposedParameters;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		TArray<class UMaterialScalarParameterWidget*> MaterialScalarParameterWidgets;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		TArray<class UMaterialVectorParameterWidget*> MaterialVectorParameterWidgets;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class UMaterialScalarParameterWidget> MaterialScalarParameterWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class UMaterialVectorParameterWidget> MaterialVectorParameterWidgetClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
		class UTextBlock* TitleTextBlock;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
		class UPanelWidget* ExposedMaterialWidgetsPanel;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
		class UButton* ConfirmButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool bCloseOnConfirm = true;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class UMaterialInstanceDynamic* MaterialInstance;

	UPROPERTY(BlueprintAssignable)
		FOnMaterialParametersConfirmed OnMaterialParametersConfirmedDelegate;

	void NativeConstruct() override;

	UFUNCTION(BlueprintCallable)
		void SetupPanel(FText WidgetName, class UMaterialSelectionMenuWidget* Parent, class UMaterialInstanceDynamic* Material);

	UFUNCTION(BlueprintCallable)
		void OnConfirmButton();

};
