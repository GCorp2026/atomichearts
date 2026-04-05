#include "InventoryComponent.h"

void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
	SetIsReplicated(true);
}

UInventoryComponent::UInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	SetIsReplicated(true);
}

void UInventoryComponent::AddItem(const FLootBoxReward& Item)
{
	if (GetOwner()->HasAuthority())
	{
		InventoryItems.Add(Item);

		if (!Item.bIsDuplicate)
		{
			OwnedItemIds.Add(Item.ItemId);
		}
		else
		{
			// Duplicate gives shards
			Shards += Item.ShardValue;
			OnShardsChanged.Broadcast(Shards);
		}

		OnItemAdded.Broadcast(Item, Item.bIsDuplicate);
	}
}

void UInventoryComponent::RemoveItem(const FString& ItemId)
{
	if (GetOwner()->HasAuthority())
	{
		int32 Index = InventoryItems.IndexOfByPredicate([&ItemId](const FLootBoxReward& Item)
		{
			return Item.ItemId == ItemId;
		});

		if (Index != INDEX_NONE)
		{
			InventoryItems.RemoveAt(Index);
			OwnedItemIds.Remove(ItemId);
			OnItemRemoved.Broadcast(ItemId);
		}
	}
}

TArray<FLootBoxReward> UInventoryComponent::GetItemsByRarity(EWeaponRarity Rarity) const
{
	TArray<FLootBoxReward> Filtered;
	for (const FLootBoxReward& Item : InventoryItems)
	{
		if (Item.Rarity == Rarity)
		{
			Filtered.Add(Item);
		}
	}
	return Filtered;
}

TArray<FLootBoxReward> UInventoryComponent::GetWeapons() const
{
	TArray<FLootBoxReward> Weapons;
	for (const FLootBoxReward& Item : InventoryItems)
	{
		if (Item.ItemType == "Weapon")
		{
			Weapons.Add(Item);
		}
	}
	return Weapons;
}

TArray<FLootBoxReward> UInventoryComponent::GetArmor() const
{
	TArray<FLootBoxReward> Armor;
	for (const FLootBoxReward& Item : InventoryItems)
	{
		if (Item.ItemType == "Armor")
		{
			Armor.Add(Item);
		}
	}
	return Armor;
}

int32 UInventoryComponent::GetDuplicateCount() const
{
	int32 Count = 0;
	for (const FLootBoxReward& Item : InventoryItems)
	{
		if (Item.bIsDuplicate)
		{
			Count++;
		}
	}
	return Count;
}

int32 UInventoryComponent::ConvertAllDuplicatesToShards()
{
	int32 TotalConverted = 0;

	if (GetOwner()->HasAuthority())
	{
		for (const FLootBoxReward& Item : InventoryItems)
		{
			if (Item.bIsDuplicate)
			{
				TotalConverted += Item.ShardValue;
			}
		}

		if (TotalConverted > 0)
		{
			Shards += TotalConverted;
			OnShardsChanged.Broadcast(Shards);

			// Remove duplicates from inventory
			InventoryItems.RemoveAll([](const FLootBoxReward& Item)
			{
				return Item.bIsDuplicate;
			});
		}
	}

	return TotalConverted;
}

bool UInventoryComponent::HasItem(const FString& ItemId) const
{
	return OwnedItemIds.Contains(ItemId);
}

void UInventoryComponent::AddShards(int32 Amount)
{
	if (GetOwner()->HasAuthority())
	{
		Shards += Amount;
		OnShardsChanged.Broadcast(Shards);
	}
}

bool UInventoryComponent::SpendShards(int32 Amount)
{
	if (Shards < Amount) return false;

	if (GetOwner()->HasAuthority())
	{
		Shards -= Amount;
		OnShardsChanged.Broadcast(Shards);
	}
	return true;
}
