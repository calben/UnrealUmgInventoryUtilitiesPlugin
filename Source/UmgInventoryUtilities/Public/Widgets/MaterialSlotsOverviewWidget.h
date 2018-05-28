// Copyright 2018 iGotchaMedia Inc.  All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MaterialSlotsOverviewWidget.generated.h"

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
		class UMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
		class UTextBlock* MenuTitleTextBlock;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
		class UPanelWidget* EditableMaterialSlotsPanelWidget;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
		class UButton* ConfirmButton;

	void NativeConstruct() override;

	UFUNCTION(BlueprintCallable)
		void SetupWidget(class UMeshComponent* MeshComponent);

	UFUNCTION(BlueprintCallable)
		void OnConfirmButton();

};
