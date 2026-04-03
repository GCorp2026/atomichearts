// Copyright 2026 Atomic Hearts Team

#include "Loot/ULootBoxManager.h"
#include "Loot/EBoxType.h"

ULootBoxManager::ULootBoxManager()
{
	BoxesPurchasedCounter = 0;
}

FLootBoxResult ULootBoxManager::OpenBox(EBoxType BoxType, int64 PlayerID)
{
	FLootBoxResult Result;

	if (BoxType == EBoxType::Premier && !IsPremierUnlocked())
	{
		UE_LOG(LogTemp, Warning, TEXT("Premier box not yet unlocked!"));
		return Result;
	}

	if (BoxType == EBoxType::Premier)
	{
		Result.bIsPremier = true;
		Result.PremierItem = GenerateWeapon(EWeaponRarity::Exotic, true);
		Result.Items.Add(Result.PremierItem);
		ResetCounter();
	}

	const int32 ItemCount = 5;
	const int32 WeaponsCount = 3;
	const int32 ArmorCount = 2;

	for (int32 i = 0; i < WeaponsCount; ++i)
	{
		bool bIsClassSpecific = (i == 0);
		Result.Items.Add(RollItem(BoxType, bIsClassSpecific));
	}

	for (int32 i = 0; i < ArmorCount; ++i)
	{
		bool bIsClassSpecific = (i == 0);
		FGeneratedItem ArmorItem = RollItem(BoxType, bIsClassSpecific);
		ArmorItem.ItemType = EItemType::Armor;
		Result.Items.Add(ArmorItem);
	}

	return Result;
}

void ULootBoxManager::AddPurchaseCounter(EBoxType BoxType)
{
	if (BoxType == EBoxType::Deluxe)
	{
		BoxesPurchasedCounter++;
		if (BoxesPurchasedCounter >= PREMIER_UNLOCK_THRESHOLD)
		{
			UE_LOG(LogTemp, Display, TEXT("Premier Box Unlocked!"));
		}
	}
	else if (BoxType == EBoxType::Premier)
	{
		ResetCounter();
	}
}

bool ULootBoxManager::IsPremierUnlocked() const
{
	return BoxesPurchasedCounter >= PREMIER_UNLOCK_THRESHOLD;
}

void ULootBoxManager::ResetCounter()
{
	BoxesPurchasedCounter = 0;
}

int32 ULootBoxManager::GetBoxCost(EBoxType BoxType) const
{
	switch (BoxType)
	{
	case EBoxType::Standard:  return STANDARD_COST;
	case EBoxType::Deluxe:    return DELUXE_COST;
	case EBoxType::Premier:   return 0;
	default:                  return 0;
	}
}

void ULootBoxManager::SetPlayerSilver(int64 PlayerID, int32 Silver)
{
	PlayerSilverMap.FindOrAdd(PlayerID) = Silver;
}

int32 ULootBoxManager::GetPlayerSilver(int64 PlayerID) const
{
	if (const int32* Silver = PlayerSilverMap.Find(PlayerID))
	{
		return *Silver;
	}
	return StartingSilver;
}

EWeaponRarity ULootBoxManager::RollRarity(EBoxType BoxType) const
{
	const float Roll = FMath::FRand() * 100.0f;

	switch (BoxType)
	{
	case EBoxType::Standard:
	{
		if (Roll < 2.0f)   return EWeaponRarity::Legendary;
		if (Roll < 10.0f)  return EWeaponRarity::Rare;
		if (Roll < 40.0f)  return EWeaponRarity::Uncommon;
		return EWeaponRarity::Common;
	}
	case EBoxType::Deluxe:
	{
		if (Roll < 2.0f)   return EWeaponRarity::Exotic;
		if (Roll < 20.0f)  return EWeaponRarity::Legendary;
		if (Roll < 60.0f)  return EWeaponRarity::Rare;
		return EWeaponRarity::Uncommon;
	}
	case EBoxType::Premier:
	{
		if (Roll < 50.0f)  return EWeaponRarity::Exotic;
		return EWeaponRarity::Legendary;
	}
	default:
		return EWeaponRarity::Common;
	}
}

FGeneratedItem ULootBoxManager::RollItem(EBoxType BoxType, bool bIsClassSpecific)
{
	EWeaponRarity Rarity = RollRarity(BoxType);
	return GenerateWeapon(Rarity, bIsClassSpecific);
}

FGeneratedItem ULootBoxManager::GenerateWeapon(EWeaponRarity Rarity, bool bClassSpecific)
{
	FGeneratedItem Item;
	Item.ItemType = EItemType::Weapon;
	Item.Rarity = Rarity;
	Item.ItemLevel = 1;

	const TArray<FString> WeaponPrefixes = {
		TEXT("Axiom"), TEXT("Neon"), TEXT("Chrome"), TEXT("Ghost"), TEXT("Drift"), TEXT("Solaris")
	};

	const TArray<FString> WeaponTypes = {
		TEXT("AR"), TEXT("SMG"), TEXT("Pulse"), TEXT("LMG"), TEXT("Shotgun"), TEXT("HC"), TEXT("Sword"), TEXT("Rocket")
	};

	FString Prefix = WeaponPrefixes[FMath::RandHelper(WeaponPrefixes.Num())];
	FString Type = WeaponTypes[FMath::RandHelper(WeaponTypes.Num())];
	FString Suffix = TEXT("X");

	switch (Rarity)
	{
	case EWeaponRarity::Common:     Suffix = TEXT("I"); break;
	case EWeaponRarity::Uncommon:   Suffix = TEXT("II"); break;
	case EWeaponRarity::Rare:       Suffix = TEXT("III"); break;
	case EWeaponRarity::Legendary:  Suffix = TEXT("IV"); break;
	case EWeaponRarity::Exotic:     Suffix = TEXT("V"); break;
	default: break;
	}

	Item.ItemName = FString::Printf(TEXT("%s %s-%s"), *Prefix, *Type, *Suffix);
	Item.ItemID = FString::Printf(TEXT("%s_%s_%d"), *Prefix, *Type, FMath::RandHelper(1000));

	return Item;
}

FGeneratedItem ULootBoxManager::GenerateArmor(EWeaponRarity Rarity)
{
	FGeneratedItem Item;
	Item.ItemType = EItemType::Armor;
	Item.Rarity = Rarity;
	Item.ItemLevel = 1;

	const TArray<FString> ArmorTypes = {
		TEXT("Helmet"), TEXT("Chest"), TEXT("Gauntlets"), TEXT("Boots"), TEXT("Class")
	};

	const TArray<FString> MaterialTypes = {
		TEXT("Chrome"), TEXT("Neon"), TEXT("Solaris"), TEXT("Drift"), TEXT("Ghost")
	};

	FString Material = MaterialTypes[FMath::RandHelper(MaterialTypes.Num())];
	FString Type = ArmorTypes[FMath::RandHelper(ArmorTypes.Num())];

	Item.ItemName = FString::Printf(TEXT("%s %s"), *Material, *Type);
	Item.ItemID = FString::Printf(TEXT("%s_%s_%d"), *Material, *Type, FMath::RandHelper(1000));

	return Item;
}
