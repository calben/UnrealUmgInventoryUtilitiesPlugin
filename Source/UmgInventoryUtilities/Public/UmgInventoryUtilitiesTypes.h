#pragma once

#include "CoreMinimal.h"
#include "UmgInventoryUtilitiesTypes.generated.h"

//UENUM(BlueprintType)
//enum class EInventoryMaterialType : uint8
//{
//	Cloth,
//	Leather,
//	Metal
//};

USTRUCT(BlueprintType)
struct FInventoryMaterialItem
{

	GENERATED_BODY()

public:

	FName Name;
	FName Type;
	class UTexture2D* PreviewImage;
};
