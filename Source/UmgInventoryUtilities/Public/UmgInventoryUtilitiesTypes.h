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
struct FEquippableItemBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString Slot;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		bool bIsEquipped;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UTexture2D *ItemPreviewTexture;
};

USTRUCT(BlueprintType)
struct FEquippableSkeletalMesh : public FEquippableItemBase
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class USkeletalMeshComponent *ItemMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class USkeletalMesh *ItemMesh;
};

USTRUCT(BlueprintType)
struct FEquippableActor : public FEquippableItemBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class AActor> ActorClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class AActor *Actor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName SocketName;
};

UENUM(BlueprintType)
enum class EHand : uint8
{
	Left,
	Right
};

UENUM(BlueprintType)
enum class EFinger : uint8
{
	Thumb,
	Index,
	Pointer,
	Ring,
	Pinky
};

USTRUCT(BlueprintType)
struct FHandEquippableActor : public FEquippableItemBase
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class USkeletalMeshComponent *ItemMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class USkeletalMesh *ItemMesh;

};

USTRUCT(BlueprintType)
struct FInventoryMaterialItem
{

	GENERATED_BODY()

public:
	FName Name;
	FName Type;
	class UTexture2D *PreviewImage;
};
