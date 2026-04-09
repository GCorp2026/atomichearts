// Copyright 2024 Destiny Cyberpunk

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EClassType.generated.h"

/**
 * Character class types for Destiny Cyberpunk
 */
UENUM(BlueprintType)
enum class EClassType : uint8
{
	TechMage       UMETA(DisplayName = "Tech Mage"),
	ChromeSentinel UMETA(DisplayName = "Chrome Sentinel"),
	NeonPhantom    UMETA(DisplayName = "Neon Phantom"),
	GhostRunner    UMETA(DisplayName = "Ghost Runner"),
	SolarisWarden  UMETA(DisplayName = "Solaris Warden")
};

/**
 * Ability slot indices
 */
UENUM(BlueprintType)
enum class EAbilitySlot : uint8
{
	Ability1 = 0,
	Ability2 = 1,
	Ability3 = 2,
	Ultimate  = 3
};

/**
 * Individual ability identifiers
 */
UENUM(BlueprintType)
enum class EAbilityType : uint8
{
	None,
	// Tech Mage
	TimeStop,
	TimeSlow,
	ChronoTrap,
	PhaseShift,
	// Chrome Sentinel
	Barricade,
	RallyShield,
	GroundPound,
	Overshield,
	// Neon Phantom
	FanTheHammer,
	Dodge,
	MarkedForDeath,
	GunKata,
	// Ghost Runner
	Vanish,
	ScoutDrone,
	Blink,
	EMPBurst,
	// Solaris Warden
	HealingRift,
	SolarGrenade,
	ImpactGrenade,
	PulseGrenade,
	Revival,
	SolarFlare
};
