// Copyright 2024 Destiny Cyberpunk

#include "UClassStatsComponent.h"
#include "EClassType.h"

UClassStatsComponent::UClassStatsComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UClassStatsComponent::BeginPlay()
{
	Super::BeginPlay();
	ApplyClassModifiers();
}

void UClassStatsComponent::SetClass(EClassType NewClass)
{
	CurrentClass = NewClass;
	ApplyClassModifiers();
}

void UClassStatsComponent::ApplyClassModifiers()
{
	// Reset to defaults
	Stats = FCharacterStats();

	switch (CurrentClass)
	{
	case EClassType::TechMage:
		// Chronokeeper subclass - crowd control mage
		Stats.MaxHealth = 80.f;      // Squishy
		Stats.Armor = 0.f;
		Stats.MovementSpeed = 620.f;
		Stats.Damage = 12.f;
		Stats.Intelligence = 80.f;
		Stats.ChronoPower = 90.f;
		Stats.CooldownReduction = 0.15f;
		break;

	case EClassType::ChromeSentinel:
		// Iron Wall subclass - tank
		Stats.MaxHealth = 200.f;     // High HP
		Stats.Armor = 50.f;          // Damage reduction
		Stats.MovementSpeed = 500.f; // Slow
		Stats.Damage = 15.f;
		Stats.Resilience = 90.f;
		Stats.Strength = 80.f;
		break;

	case EClassType::NeonPhantom:
		// Quickdraw subclass - gunslinger DPS
		Stats.MaxHealth = 100.f;
		Stats.Armor = 10.f;
		Stats.MovementSpeed = 700.f; // Fast
		Stats.Damage = 18.f;
		Stats.CriticalChance = 0.15f;
		Stats.Precision = 85.f;
		Stats.Agility = 80.f;
		Stats.Mobility = 85.f;
		break;

	case EClassType::GhostRunner:
		// Shadow subclass - scout/stealth
		Stats.MaxHealth = 90.f;
		Stats.Armor = 5.f;
		Stats.MovementSpeed = 680.f;
		Stats.Damage = 14.f;
		Stats.Stealth = 90.f;
		Stats.Tech = 85.f;
		Stats.Speed = 80.f;
		break;

	case EClassType::SolarisWarden:
		// Lightbearer subclass - healer/support
		Stats.MaxHealth = 110.f;
		Stats.Armor = 15.f;
		Stats.MovementSpeed = 580.f;
		Stats.Damage = 8.f;
		Stats.Restoration = 90.f;
		Stats.Radiance = 85.f;
		Stats.Benevolence = 80.f;
		break;
	}
}

float UClassStatsComponent::GetStat(const FString& StatName) const
{
	if (StatName == "MaxHealth") return Stats.MaxHealth;
	if (StatName == "Armor") return Stats.Armor;
	if (StatName == "MovementSpeed") return Stats.MovementSpeed;
	if (StatName == "Damage") return Stats.Damage;
	if (StatName == "Intelligence") return Stats.Intelligence;
	if (StatName == "ChronoPower") return Stats.ChronoPower;
	if (StatName == "Resilience") return Stats.Resilience;
	if (StatName == "Strength") return Stats.Strength;
	if (StatName == "Mobility") return Stats.Mobility;
	if (StatName == "Precision") return Stats.Precision;
	if (StatName == "Stealth") return Stats.Stealth;
	if (StatName == "Tech") return Stats.Tech;
	if (StatName == "Restoration") return Stats.Restoration;
	if (StatName == "Radiance") return Stats.Radiance;
	return 0.f;
}

float UClassStatsComponent::GetEffectiveMaxHealth() const
{
	// Chrome Sentinel Resilience boosts max HP
	if (CurrentClass == EClassType::ChromeSentinel)
	{
		return Stats.MaxHealth * (1.f + (Stats.Resilience - 50.f) * 0.01f);
	}
	return Stats.MaxHealth;
}

float UClassStatsComponent::GetEffectiveArmor() const
{
	// Chrome Sentinel gets bonus armor from Strength
	if (CurrentClass == EClassType::ChromeSentinel)
	{
		return Stats.Armor + (Stats.Strength - 50.f) * 0.2f;
	}
	return Stats.Armor;
}

float UClassStatsComponent::GetEffectiveMoveSpeed() const
{
	// Neon Phantom Mobility boosts speed
	if (CurrentClass == EClassType::NeonPhantom)
	{
		return Stats.MovementSpeed * (1.f + (Stats.Mobility - 50.f) * 0.005f);
	}
	// Ghost Runner Speed bonus
	if (CurrentClass == EClassType::GhostRunner)
	{
		return Stats.MovementSpeed * (1.f + (Stats.Speed - 50.f) * 0.004f);
	}
	return Stats.MovementSpeed;
}

float UClassStatsComponent::GetEffectiveDamage() const
{
	// Tech Mage Intelligence boosts skill damage
	if (CurrentClass == EClassType::TechMage)
	{
		return Stats.Damage * (1.f + (Stats.Intelligence - 50.f) * 0.01f);
	}
	// Neon Phantom Precision affects crit damage
	if (CurrentClass == EClassType::NeonPhantom)
	{
		return Stats.Damage * (1.f + (Stats.Precision - 50.f) * 0.008f);
	}
	return Stats.Damage;
}
