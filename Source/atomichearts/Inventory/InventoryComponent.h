#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LootBoxData.h"
#include "InventoryComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnItemAdded, const FLootBoxReward&, Item, bool, bIsDuplicate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnItemRemoved, const FString&, ItemId);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnShardsChanged, int32, NewTotal);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ATOMICHEARTS_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UInventoryComponent();

protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void AddItem(const FLootBoxReward& Item);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void RemoveItem(const FString& ItemId);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	TArray<FLootBoxReward> GetItemsByRarity(EWeaponRarity Rarity) const;

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	TArray<FLootBoxReward> GetWeapons() const;

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	TArray<FLootBoxReward> GetArmor() const;

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	int32 GetDuplicateCount() const;

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	int32 ConvertAllDuplicatesToShards();

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void AddShards(int32 Amount);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool SpendShards(int32 Amount);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	int32 GetShards() const { return Shards; }

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool HasItem(const FString& ItemId) const;

public:
	UPROPERTY(BlueprintAssignable, Category = "Inventory")
	FOnItemAdded OnItemAdded;

	UPROPERTY(BlueprintAssignable, Category = "Inventory")
	FOnItemRemoved OnItemRemoved;

	UPROPERTY(BlueprintAssignable, Category = "Inventory")
	FOnShardsChanged OnShardsChanged;

protected:
	UPROPERTY(Replicated)
	TArray<FLootBoxReward> InventoryItems;

	UPROPERTY(Replicated)
	int32 Shards = 0;

	UPROPERTY(Replicated)
	TArray<FString> OwnedItemIds;
};
