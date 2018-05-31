// Copyright 2018 iGotchaMedia Inc.  All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
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
		class UMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class UMaterialSlotsOverviewWidget* MaterialSlotsOverviewWidget;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		FName SlotName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class UMaterialSelectionMenuWidget> MaterialSelectionMenuWidgetClass;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
		class UTextBlock* NameTextBlock;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
		class UButton* EditButton;

	void NativeConstruct() override;

	UFUNCTION(BlueprintCallable)
		void SetupWidget(UMaterialSlotsOverviewWidget* Parent, FName Name, class UMeshComponent* MeshComponent);

	UFUNCTION(BlueprintCallable)
		void OnEdit();

};
