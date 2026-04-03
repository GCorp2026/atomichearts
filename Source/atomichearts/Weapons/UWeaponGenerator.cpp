// Copyright 2026 Atomic Hearts Team

#include "Weapons/UWeaponGenerator.h"
#include "Weapons/EWeaponRarity.h"
#include "Weapons/EWeaponSlot.h"

UWeaponGenerator::UWeaponGenerator() {}

// Faction prefixes
const TArray<FString> UWeaponGenerator::AxiomPrefixes = { "Protocol", "Mainframe", "Enforcer", "Overkill", "Prime" };
const TArray<FString> UWeaponGenerator::NeonPrefixes  = { "Street", "Viper", "Shadow", "Jackal" };
const TArray<FString> UWeaponGenerator::ChromePrefixes = { "Patriot", "Duty", "Marshal", "Eagle", "Iron" };
const TArray<FString> UWeaponGenerator::GhostPrefixes  = { "Phantom", "Cipher", "Ghost", "Silent", "Void" };
const TArray<FString> UWeaponGenerator::SolarisPrefixes = { "Radiant", "Corona", "Nova", "Solar", "Flare" };
const TArray<FString> UWeaponGenerator::DriftPrefixes  = { "Abyss", "Void", "Madness", "Rift", "Eldritch" };

// Base types by slot category
const TArray<FString> UWeaponGenerator::BaseTypes = {
	"Assault Rifle", "Pulse Rifle", "Scout Rifle", "Hand Cannon", "Submachine Gun",
	"Shotgun", "Rocket Launcher", "Machine Gun", "Sword", "Grenade Launcher"
};

const TArray<FString> UWeaponGenerator::ElementalSuffixes = { "of the Fire", "of the Ice", "of the Lightning", "of the Void", "of the Solar" };
const TArray<FString> UWeaponGenerator::StatSuffixes = { "of Damage", "of Precision", "of Velocity", "of Stability" };
const TArray<FString> UWeaponGenerator::AdjectiveSuffixes = { "Swift", "Deadly", "Eternal", "Vengeful" };

uint32 UWeaponGenerator::FNV1aHash(int32 Seed, uint32 Salt) const
{
	uint32 Hash = 2166136261u;
	uint32 Combined = static_cast<uint32>(Seed) ^ Salt;
	uint8* Data = reinterpret_cast<uint8*>(&Combined);
	for (int32 I = 0; I < sizeof(Combined); ++I) { Hash ^= Data[I]; Hash *= 16777619u; }
	return Hash;
}

int32 UWeaponGenerator::SlotToBaseTypeIndex(EWeaponSlot Slot)
{
	switch (Slot)
	{
		case EWeaponSlot::Primary_AR:   return 0; case EWeaponSlot::Primary_PR:   return 1;
		case EWeaponSlot::Primary_SR:   return 2; case EWeaponSlot::Secondary_HC: return 3;
		case EWeaponSlot::Secondary_SMG: return 4; case EWeaponSlot::Secondary_SG: return 5;
		case EWeaponSlot::Heavy_RL:     return 6; case EWeaponSlot::Heavy_LMG:    return 7;
		case EWeaponSlot::Heavy_SW:     return 8; case EWeaponSlot::Heavy_GL:     return 9;
		default: return 0;
	}
}

int32 UWeaponGenerator::GetPerkCountForRarity(EWeaponRarity Rarity) const
{
	switch (Rarity)
	{
		case EWeaponRarity::Common:    return FMath::RandRange(1, 2);
		case EWeaponRarity::Uncommon:  return FMath::RandRange(2, 3);
		case EWeaponRarity::Rare:      return FMath::RandRange(3, 4);
		case EWeaponRarity::Legendary: return FMath::RandRange(4, 5);
		case EWeaponRarity::Exotic:    return 5;
		default: return 1;
	}
}

FLinearColor UWeaponGenerator::GetBorderColorForRarity(EWeaponRarity Rarity) const
{
	switch (Rarity)
	{
		case EWeaponRarity::Common:    return FLinearColor(0.8f, 0.8f, 0.8f, 1.0f);
		case EWeaponRarity::Uncommon:  return FLinearColor(0.2f, 0.8f, 0.2f, 1.0f);
		case EWeaponRarity::Rare:      return FLinearColor(0.2f, 0.4f, 1.0f, 1.0f);
		case EWeaponRarity::Legendary: return FLinearColor(1.0f, 0.5f, 0.0f, 1.0f);
		case EWeaponRarity::Exotic:    return FLinearColor(1.0f, 0.84f, 0.0f, 1.0f);
		default: return FLinearColor::White;
	}
}

FString UWeaponGenerator::GenerateWeaponName(EWeaponSlot Slot, int32 Seed)
{
	const int32 FactionIdx = FNV1aHash(Seed, 1) % 6;
	const int32 PrefixIdx = FNV1aHash(Seed, 2) % 5;
	const int32 BaseIdx = SlotToBaseTypeIndex(Slot);
	const int32 SuffixIdx = FNV1aHash(Seed, 3) % 8;

	const TArray<FString>* FactionArray = nullptr;
	switch (FactionIdx)
	{
		case 0: FactionArray = &AxiomPrefixes; break; case 1: FactionArray = &NeonPrefixes; break;
		case 2: FactionArray = &ChromePrefixes; break; case 3: FactionArray = &GhostPrefixes; break;
		case 4: FactionArray = &SolarisPrefixes; break; case 5: FactionArray = &DriftPrefixes; break;
	}
	FString FactionPrefix = (*FactionArray)[PrefixIdx % FactionArray->Num()];

	FString Suffix;
	if (SuffixIdx < 5) Suffix = ElementalSuffixes[SuffixIdx];
	else if (SuffixIdx < 8) Suffix = StatSuffixes[SuffixIdx - 5];
	else Suffix = AdjectiveSuffixes[SuffixIdx - 8];

	return FString::Printf(TEXT("%s %s %s"), *FactionPrefix, *BaseTypes[BaseIdx], *Suffix);
}

FWeaponStats UWeaponGenerator::GenerateStats(EWeaponSlot Slot, EWeaponRarity Rarity, int32 Seed)
{
	FWeaponStats Stats;
	const float RarityMult = (static_cast<int32>(Rarity) + 1) / 5.0f;
	const float Roll = FMath::RandHelper(10000) / 10000.0f;
	const float RarityBonus = RarityMult * 0.5f;

	// Base damage by slot
	switch (Slot)
	{
		case EWeaponSlot::Secondary_SG: Stats.Damage = 80.f; break;
		case EWeaponSlot::Secondary_HC: Stats.Damage = 60.f; break;
		case EWeaponSlot::Heavy_RL: Stats.Damage = 150.f; break;
		case EWeaponSlot::Heavy_GL: Stats.Damage = 120.f; break;
		case EWeaponSlot::Primary_AR: Stats.Damage = 25.f; break;
		case EWeaponSlot::Primary_PR: Stats.Damage = 22.f; break;
		case EWeaponSlot::Primary_SR: Stats.Damage = 45.f; break;
		case EWeaponSlot::Secondary_SMG: Stats.Damage = 18.f; break;
		case EWeaponSlot::Heavy_LMG: Stats.Damage = 30.f; break;
		case EWeaponSlot::Heavy_SW: Stats.Damage = 100.f; break;
		default: Stats.Damage = 20.f;
	}
	Stats.Damage *= (0.7f + (Roll * 0.3f) + RarityBonus);
	Stats.FireRate = FMath::Lerp(1.0f, 0.05f, FMath::RandHelper(10000) / 10000.0f);
	Stats.Range = FMath::Lerp(5000.f, 15000.f, (FMath::RandHelper(10000) / 10000.0f) * RarityMult);
	Stats.Accuracy = FMath::Clamp(0.5f + (FMath::RandHelper(5000) / 10000.0f) + (RarityMult * 0.2f), 0.5f, 1.0f);
	Stats.MaxRange = Stats.Range * 2.0f;
	return Stats;
}

TArray<FWeaponPerk> UWeaponGenerator::GeneratePerks(EWeaponRarity Rarity, int32 Seed)
{
	TArray<FWeaponPerk> Perks;
	const int32 PerkCount = GetPerkCountForRarity(Rarity);
	const TArray<FString> PerkNames = { "Rampage", "Kill Clip", "Multi-Kill Clip", "Quickdraw", "Snapshot", "Auto-Loading", "Incendiary", "Cryo Rounds", "Shock Rounds", "Void Burst" };
	const TArray<FLinearColor> PerkColors = { FLinearColor(1.f, 0.3f, 0.3f), FLinearColor(0.3f, 1.f, 0.3f), FLinearColor(1.f, 0.8f, 0.2f), FLinearColor(0.5f, 0.5f, 1.f), FLinearColor(0.7f, 0.7f, 1.f) };

	for (int32 I = 0; I < PerkCount; ++I)
	{
		const uint32 PerkSeed = FNV1aHash(Seed, 100 + I);
		FWeaponPerk Perk;
		Perk.PerkName = PerkNames[PerkSeed % PerkNames.Num()];
		Perk.Description = FString::Printf(TEXT("Rank %d bonus"), (PerkSeed >> 8) % 3 + 1);
		Perk.PerkRank = (PerkSeed >> 8) % 3 + 1;
		Perk.PerkColor = PerkColors[I % PerkColors.Num()];
		Perks.Add(Perk);
	}
	return Perks;
}

FWeaponGeneratorResult UWeaponGenerator::GetExoticWeapon(FName ExoticName, EWeaponSlot Slot, int32 Seed)
{
	FWeaponGeneratorResult Result = { FString(), FString(), Slot, EWeaponRarity::Exotic, FWeaponStats(), TArray<FWeaponPerk>(), FLinearColor(1.0f, 0.84f, 0.0f, 1.0f) };
	Result.UniqueID = FString::Printf(TEXT("EXOTIC_%s_%d"), *ExoticName.ToString(), Seed);

	FWeaponPerk Perk; Perk.PerkRank = 3;
	if (ExoticName == TEXT("Galleria Horn"))
	{
		Result.WeaponName = "Galleria Horn";
		Result.Stats = { 200.f, 0.8f, 10000.f, 0.9f, 2.0f, 0.5f, 1.0f, 1.0f, 0.8f, 8.f };
		Perk = { "Wolfpack Rounds", "Homing cluster bombs track multiple targets", 3, FLinearColor(1.f, 0.5f, 0.f) };
	}
	else if (ExoticName == TEXT("The Fabricator"))
	{
		Result.WeaponName = "The Fabricator";
		Result.Stats = { 35.f, 0.1f, 8000.f, 0.95f, 2.0f, 0.5f, 1.0f, 1.0f, 0.9f, 10.f };
		Perk = { "Neural Link", "Creates markers; damage buff to marked allies", 3, FLinearColor(0.5f, 0.f, 1.f) };
	}
	else if (ExoticName == TEXT("Chrome Fury"))
	{
		Result.WeaponName = "Chrome Fury";
		Result.Stats = { 90.f, 0.15f, 4000.f, 0.95f, 2.0f, 0.5f, 1.0f, 1.0f, 0.85f, 7.f };
		Perk = { "Trench Barrel", "Damage increases with consecutive hits", 3, FLinearColor(0.f, 0.8f, 1.f) };
	}
	else if (ExoticName == TEXT("Void Walker"))
	{
		Result.WeaponName = "Void Walker";
		Result.Stats = { 40.f, 0.2f, 12000.f, 0.85f, 2.0f, 0.5f, 1.0f, 1.0f, 0.8f, 5.f };
		Perk = { "Desperado", "Faster fire rate after precision kill", 3, FLinearColor(0.5f, 0.f, 0.8f) };
	}
	else if (ExoticName == TEXT("Solaris Edge"))
	{
		Result.WeaponName = "Solaris Edge";
		Result.Stats = { 150.f, 1.0f, 2000.f, 1.0f, 2.0f, 0.5f, 1.0f, 1.0f, 0.9f, 1.f };
		Perk = { "Guillotine", "Heavy attack damage buff; throws and returns", 3, FLinearColor(1.f, 0.6f, 0.f) };
	}
	Result.Perks.Add(Perk);
	return Result;
}

FWeaponGeneratorResult UWeaponGenerator::GenerateWeapon(int32 Seed, EWeaponSlot Slot, EWeaponRarity Rarity)
{
	// Exotic pre-designed weapons - check by matching Slot
	if (Rarity == EWeaponRarity::Exotic)
	{
		if (Slot == EWeaponSlot::Heavy_RL && FNV1aHash(Seed, 500) % 3 == 0) return GetExoticWeapon(TEXT("Galleria Horn"), Slot, Seed);
		if (Slot == EWeaponSlot::Primary_PR && FNV1aHash(Seed, 501) % 3 == 0) return GetExoticWeapon(TEXT("The Fabricator"), Slot, Seed);
		if (Slot == EWeaponSlot::Secondary_SG && FNV1aHash(Seed, 502) % 3 == 0) return GetExoticWeapon(TEXT("Chrome Fury"), Slot, Seed);
		if (Slot == EWeaponSlot::Primary_PR && FNV1aHash(Seed, 503) % 3 == 0) return GetExoticWeapon(TEXT("Void Walker"), Slot, Seed);
		if (Slot == EWeaponSlot::Heavy_SW && FNV1aHash(Seed, 504) % 3 == 0) return GetExoticWeapon(TEXT("Solaris Edge"), Slot, Seed);
	}

	// Procedural fallback
	FWeaponGeneratorResult Result;
	Result.WeaponName = GenerateWeaponName(Slot, Seed);
	Result.UniqueID = FString::Printf(TEXT("PROC_%d_%d"), static_cast<int32>(Slot), Seed);
	Result.Slot = Slot; Result.Rarity = Rarity;
	Result.Stats = GenerateStats(Slot, Rarity, Seed);
	Result.Perks = GeneratePerks(Rarity, Seed);
	Result.BorderColor = GetBorderColorForRarity(Rarity);
	return Result;
}
