// Copyright 2026 Atomic Hearts Team

#pragma once

#include "CoreMinimal.h"
#include "EBoxType.generated.h"

UENUM(BlueprintType)
enum class EBoxType : uint8
{
	Standard  UMETA(DisplayName = "Standard Box"),
	Deluxe    UMETA(DisplayName = "Deluxe Box"),
	Premier   UMETA(DisplayName = "Premier Box")
};

UENUM(BlueprintType)
enum class EWeaponRarity : uint8
{
	Common     UMETA(DisplayName = "Common"),
	Uncommon   UMETA(DisplayName = "Uncommon"),
	Rare       UMETA(DisplayName = "Rare"),
	Legendary  UMETA(DisplayName = "Legendary"),
	Exotic     UMETA(DisplayName = "Exotic")
};

UENUM(BlueprintType)
enum class EItemType : uint8
{
	Weapon  UMETA(DisplayName = "Weapon"),
	Armor   UMETA(DisplayName = "Armor")
};

USTRUCT(BlueprintType)
struct FGeneratedItem
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Loot")
	FString ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Loot")
	EItemType ItemType = EItemType::Weapon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Loot")
	EWeaponRarity Rarity = EWeaponRarity::Common;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Loot")
	FString ItemID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Loot")
	int32 ItemLevel = 1;
};

USTRUCT(BlueprintType)
struct FLootBoxResult
{
	GENERATED_BODY()

	UPROPERTY()
	TArray<FGeneratedItem> Items;

	UPROPERTY()
	bool bIsPremier = false;

	UPROPERTY()
	FGeneratedItem PremierItem;
};
