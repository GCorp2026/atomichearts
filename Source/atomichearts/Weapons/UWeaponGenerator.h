// Copyright 2026 Atomic Hearts Team

#pragma once

#include "CoreMinimal.h"
#include "EWeaponRarity.h"
#include "EWeaponSlot.h"
#include "FWeaponGeneratorResult.h"
#include "FWeaponPerk.h"
#include "AtomicheartsWeaponTypes.h"
#include "UWeaponGenerator.generated.h"

/**
 * Procedural weapon generator using seeded FNV1a hash
 */
UCLASS(BlueprintType)
class ATOMICHEARTS_API UWeaponGenerator : public UObject
{
	GENERATED_BODY()

public:
	UWeaponGenerator();

	UFUNCTION(BlueprintCallable, Category = "Weapon Generator")
	FWeaponGeneratorResult GenerateWeapon(int32 Seed, EWeaponSlot Slot, EWeaponRarity Rarity);

	UFUNCTION(BlueprintCallable, Category = "Weapon Generator")
	FString GenerateWeaponName(EWeaponSlot Slot, int32 Seed);

	UFUNCTION(BlueprintCallable, Category = "Weapon Generator")
	FWeaponStats GenerateStats(EWeaponSlot Slot, EWeaponRarity Rarity, int32 Seed);

	UFUNCTION(BlueprintCallable, Category = "Weapon Generator")
	TArray<FWeaponPerk> GeneratePerks(EWeaponRarity Rarity, int32 Seed);

protected:
	// Faction prefixes per slot
	static const TArray<FString> AxiomPrefixes;
	static const TArray<FString> NeonPrefixes;
	static const TArray<FString> ChromePrefixes;
	static const TArray<FString> GhostPrefixes;
	static const TArray<FString> SolarisPrefixes;
	static const TArray<FString> DriftPrefixes;

	// Base weapon types per slot
	static const TArray<FString> BaseTypes;

	// Suffixes
	static const TArray<FString> ElementalSuffixes;
	static const TArray<FString> StatSuffixes;
	static const TArray<FString> AdjectiveSuffixes;

	// FNV1a hash for determinism
	uint32 FNV1aHash(int32 Seed, uint32 Salt = 0) const;

	// Rarity helpers
	int32 GetPerkCountForRarity(EWeaponRarity Rarity) const;
	FLinearColor GetBorderColorForRarity(EWeaponRarity Rarity) const;

	// Slot to base type index
	static int32 SlotToBaseTypeIndex(EWeaponSlot Slot);

	// Exotic weapons
	FWeaponGeneratorResult GetExoticWeapon(FName ExoticName, EWeaponSlot Slot, int32 Seed);
};
