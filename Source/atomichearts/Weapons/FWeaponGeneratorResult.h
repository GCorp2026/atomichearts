// Copyright 2026 Atomic Hearts Team

#pragma once

#include "CoreMinimal.h"
#include "EWeaponRarity.h"
#include "EWeaponSlot.h"
#include "AtomicheartsWeaponTypes.h"
#include "FWeaponPerk.h"

#include "FWeaponGeneratorResult.generated.h"

USTRUCT(BlueprintType)
struct FWeaponGeneratorResult
{
	GENERATED_BODY()

	UPROPERTY()
	FString WeaponName;

	UPROPERTY()
	FString UniqueID;

	UPROPERTY()
	EWeaponSlot Slot;

	UPROPERTY()
	EWeaponRarity Rarity;

	UPROPERTY()
	FWeaponStats Stats;

	UPROPERTY()
	TArray<FWeaponPerk> Perks;

	UPROPERTY()
	FLinearColor BorderColor;
};
