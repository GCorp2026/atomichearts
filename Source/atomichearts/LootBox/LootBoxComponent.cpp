#include "LootBoxComponent.h"
#include "Kismet/GameplayStatics.h"

void ULootBoxComponent::BeginPlay()
{
	Super::BeginPlay();
	SetIsReplicated(true);
}

ULootBoxComponent::ULootBoxComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	SetIsReplicated(true);
}

bool ULootBoxComponent::HasEnoughSilver(ELootBoxType Type) const
{
	const int32 Cost = (Type == ELootBoxType::Standard) ? 100 : 500;
	return SilverBalance >= Cost;
}

void ULootBoxComponent::OpenLootBox(ELootBoxType Type)
{
	if (GetOwner()->HasAuthority())
	{
		ServerOpenLootBox(Type);
	}
	else
	{
		ServerOpenLootBox(Type);
	}
}

void ULootBoxComponent::ServerOpenLootBox_Implementation(ELootBoxType Type)
{
	if (bIsOpening) return;

	const int32 Cost = (Type == ELootBoxType::Standard) ? 100 : 500;

	// Check premier eligibility
	if (Type != ELootBoxType::Premier && !HasEnoughSilver(Type))
	{
		return;
	}

	// If Premier, check counter
	if (Type == ELootBoxType::Premier && !ShouldGrantPremier())
	{
		return;
	}

	bIsOpening = true;

	if (Type != ELootBoxType::Premier)
	{
		SpendSilver(Cost);
	}

	// Generate loot
	PendingResult = GenerateLootBoxResult(Type);

	// Update deluxe counter
	if (Type == ELootBoxType::Deluxe)
	{
		DeluxeCounter++;
		if (ShouldGrantPremier())
		{
			UE_LOG(LogTemp, Log, TEXT("Premier unlocked! Counter: %d"), DeluxeCounter);
		}
	}

	// If Premier used, reset counter
	if (Type == ELootBoxType::Premier)
	{
		DeluxeCounter = 0;
	}

	bIsOpening = false;
	OnLootBoxOpened.Broadcast(PendingResult);
}

void ULootBoxComponent::SkipAnimation()
{
	OnLootBoxReady.Broadcast();
}

FLootBoxResult ULootBoxComponent::GenerateLootBoxResult(ELootBoxType Type)
{
	FLootBoxResult Result;

	// Generate 5 items
	for (int32 i = 0; i < 5; ++i)
	{
		EWeaponRarity Rarity = RollRarity(Type);
		FLootBoxReward Item = GenerateItem(Type, Rarity);
		Result.Items.Add(Item);
	}

	// Premier gets guaranteed exotic/legendary
	if (Type == ELootBoxType::Premier)
	{
		Result.bIsPremier = true;
		EWeaponRarity PremierRarity = (FMath::RandBool() && DeluxeCounter < 30)
			? EWeaponRarity::Legendary : EWeaponRarity::Exotic;
		Result.PremierItem = GenerateItem(Type, PremierRarity);
		Result.PremierItem.ItemType = "Premier";
	}

	// Deluxe gets dust
	if (Type == ELootBoxType::Deluxe)
	{
		Result.DustEarned = 50;
		GrantDust(Result.DustEarned);
	}

	return Result;
}

EWeaponRarity ULootBoxComponent::RollRarity(ELootBoxType Type)
{
	float Roll = FMath::FRand();

	const TMap<EWeaponRarity, float>* Chances = nullptr;
	if (Type == ELootBoxType::Standard) Chances = &StandardRarityChances;
	else if (Type == ELootBoxType::Deluxe) Chances = &DeluxeRarityChances;
	else Chances = &PremierRarityChances;

	float Cumulative = 0.0f;
	for (const auto& Pair : *Chances)
	{
		Cumulative += Pair.Value;
		if (Roll < Cumulative)
		{
			return Pair.Key;
		}
	}

	return EWeaponRarity::Common;
}

FLootBoxReward ULootBoxComponent::GenerateItem(ELootBoxType Type, EWeaponRarity Rarity)
{
	FLootBoxReward Reward;

	// Generate item based on type
	const bool bIsWeapon = FMath::RandBool();

	FString BaseName;
	if (bIsWeapon)
	{
		BaseName = "Weapon_" + FGuid::NewGuid().ToString().Left(8);
		Reward.ItemType = "Weapon";
	}
	else
	{
		BaseName = "Armor_" + FGuid::NewGuid().ToString().Left(8);
		Reward.ItemType = "Armor";
	}

	Reward.ItemId = BaseName;
	Reward.ItemName = BaseName;
	Reward.Rarity = Rarity;

	// Check duplicate
	Reward.bIsDuplicate = CheckIsDuplicate(Reward.ItemId);
	if (Reward.bIsDuplicate)
	{
		ConvertDuplicateToShards(Reward);
	}
	else
	{
		OwnedItemIds.Add(Reward.ItemId);
	}

	// Set shard value based on rarity
	switch (Rarity)
	{
	case EWeaponRarity::Common: Reward.ShardValue = 10; break;
	case EWeaponRarity::Uncommon: Reward.ShardValue = 25; break;
	case EWeaponRarity::Rare: Reward.ShardValue = 50; break;
	case EWeaponRarity::Legendary: Reward.ShardValue = 100; break;
	case EWeaponRarity::Exotic: Reward.ShardValue = 250; break;
	}

	return Reward;
}

bool ULootBoxComponent::CheckIsDuplicate(const FString& ItemId)
{
	return OwnedItemIds.Contains(ItemId);
}

void ULootBoxComponent::ConvertDuplicateToShards(const FLootBoxReward& Item)
{
	TotalShards += Item.ShardValue;
}

void ULootBoxComponent::GrantDust(int32 Amount)
{
	DustCurrency += Amount;
}

void ULootBoxComponent::AddDailyLoginReward()
{
	AddSilver(100);
}

void ULootBoxComponent::AddStrikeReward()
{
	AddSilver(50);
}

void ULootBoxComponent::AddCrucibleWinReward()
{
	AddSilver(75);
}

void ULootBoxComponent::AddRaidCompletionReward()
{
	AddSilver(200);
}

void ULootBoxComponent::AddSilver(int32 Amount)
{
	if (GetOwner()->HasAuthority())
	{
		SilverBalance += Amount;
		OnSilverChanged.Broadcast(SilverBalance);
	}
}

bool ULootBoxComponent::SpendSilver(int32 Amount)
{
	if (SilverBalance < Amount) return false;

	if (GetOwner()->HasAuthority())
	{
		SilverBalance -= Amount;
		OnSilverChanged.Broadcast(SilverBalance);
	}
	return true;
}

void ULootBoxComponent::ServerSpendSilver_Implementation(int32 Amount)
{
	SpendSilver(Amount);
}

void ULootBoxComponent::SkipAnimation_Implementation()
{
	OnLootBoxReady.Broadcast();
}
