#pragma once

#include "CoreMinimal.h"
#include "LootBoxData.generated.h"

UENUM(BlueprintType)
enum class ELootBoxType : uint8
{
	Standard	UMETA(DisplayName = "Standard"),
	Deluxe		UMETA(DisplayName = "Deluxe"),
	Premier		UMETA(DisplayName = "Premier")
};

UENUM(BlueprintType)
enum class EWeaponRarity : uint8
{
	Common		UMETA(DisplayName = "Common"),
	Uncommon	UMETA(DisplayName = "Uncommon"),
	Rare		UMETA(DisplayName = "Rare"),
	Legendary	UMETA(DisplayName = "Legendary"),
	Exotic		UMETA(DisplayName = "Exotic")
};

USTRUCT(BlueprintType)
struct FLootBoxReward
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	FString ItemId;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	FString ItemName;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	FString ItemType; // Weapon, Armor, etc.

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	EWeaponRarity Rarity = EWeaponRarity::Common;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	bool bIsDuplicate = false;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	int32 ShardValue = 0;
};

USTRUCT(BlueprintType)
struct FLootBoxResult
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	TArray<FLootBoxReward> Items;

	UPROPERTY(BlueprintReadWrite)
	bool bIsPremier = false;

	UPROPERTY(BlueprintReadWrite)
	FLootBoxReward PremierItem;

	UPROPERTY(BlueprintReadWrite)
	int32 DustEarned = 0;
};

USTRUCT()
struct FLootBoxCost
{
	GENERATED_BODY()

	int32 SilverCost = 0;
	int32 DustCost = 0;
};

UCLASS(BlueprintType, Blueprintable)
class ATOMICHEARTS_API ULootBoxData : public UDataTable
{
	GENERATED_BODY()

public:
	// Costs per box type
	FLootBoxCost GetBoxCost(ELootBoxType Type) const;

	// Rarity chances per box type (returns cumulative chance threshold)
	float GetRarityChance(ELootBoxType Type, EWeaponRarity Rarity) const;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Loot Box")
	TMap<ELootBoxType, int32> BoxCosts;

	// Rarity distribution per box type
	UPROPERTY(EditDefaultsOnly, Category = "Loot Box")
	TMap<ELootBoxType, TMap<EWeaponRarity, float>> RarityDistribution;
};
