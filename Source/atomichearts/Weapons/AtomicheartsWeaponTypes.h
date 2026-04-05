// Copyright 2026 Atomic Hearts Team

#pragma once

#include "CoreMinimal.h"
#include "AtomicheartsWeaponTypes.generated.h"

UENUM(BlueprintType)
enum class EWeaponSlot : uint8
{
	EWS_Primary   UMETA(DisplayName = "Primary"),
	EWS_Secondary UMETA(DisplayName = "Secondary"),
	EWS_Heavy    UMETA(DisplayName = "Heavy"),

	EWS_MAX UMETA(DisplayName = "Default MAX")
};

UENUM(BlueprintType)
enum class EAmmoType : uint8
{
	EAT_Ballistic   UMETA(DisplayName = "Ballistic"),
	EAT_Energy      UMETA(DisplayName = "Energy"),
	EAT_Explosive   UMETA(DisplayName = "Explosive"),
	EAT_Plasma      UMETA(DisplayName = "Plasma"),

	EAT_MAX UMETA(DisplayName = "Default MAX")
};

USTRUCT(BlueprintType)
struct FWeaponStats
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Stats")
	float Damage = 20.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Stats")
	float FireRate = 0.25f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Stats")
	float Range = 5000.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Stats")
	float Accuracy = 0.85f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Stats")
	float HeadshotMultiplier = 2.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Stats")
	float LegshotMultiplier = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Stats")
	float MaxRange = 10000.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Stats")
	float CriticalChance = 0.15f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Stats")
	float CriticalMultiplier = 1.5f;
};
