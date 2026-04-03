// Copyright 2024 Destiny Cyberpunk

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EClassType.h"
#include "UClassStatsComponent.generated.h"

/**
 * Core stats shared across all classes
 */
USTRUCT(BlueprintType)
struct FCharacterStats
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxHealth = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Armor = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MovementSpeed = 600.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Damage = 10.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CriticalChance = 0.05f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CriticalDamage = 1.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CooldownReduction = 0.f;

	// Class-specific stats
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Intelligence = 50.f;    // Tech Mage skill damage

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ChronoPower = 50.f;      // Tech Mage ultimate charge

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Resilience = 50.f;       // Chrome Sentinel HP

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Strength = 50.f;         // Chrome Sentinel melee

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Mobility = 50.f;          // Neon Phantom speed

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Precision = 50.f;        // Neon Phantom crit damage

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Agility = 50.f;           // Neon Phantom dodge

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Stealth = 50.f;           // Ghost Runner invisibility

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Tech = 50.f;              // Ghost Runner hack strength

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Speed = 50.f;            // Ghost Runner travel

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Restoration = 50.f;      // Solaris Warden healing

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Radiance = 50.f;          // Solaris Warden ultimate

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Benevolence = 50.f;      // Solaris Warden ally buff
};

/**
 * Component managing class-specific stat modifiers and getters
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ATOMICHEARTS_API UClassStatsComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UClassStatsComponent();

	/** Set class type and apply stat modifiers */
	UFUNCTION(BlueprintCallable)
	void SetClass(EClassType NewClass);

	/** Get current class */
	UFUNCTION(BlueprintPure)
	EClassType GetClass() const { return CurrentClass; }

	/** Get current stats struct */
	UFUNCTION(BlueprintPure)
	FCharacterStats GetStats() const { return Stats; }

	/** Get a single stat by name */
	UFUNCTION(BlueprintPure)
	float GetStat(const FString& StatName) const;

	/** Get effective max health including class bonuses */
	UFUNCTION(BlueprintPure)
	float GetEffectiveMaxHealth() const;

	/** Get effective armor including class bonuses */
	UFUNCTION(BlueprintPure)
	float GetEffectiveArmor() const;

	/** Get effective movement speed */
	UFUNCTION(BlueprintPure)
	float GetEffectiveMoveSpeed() const;

	/** Get effective damage */
	UFUNCTION(BlueprintPure)
	float GetEffectiveDamage() const;

	/** Tech Mage: Get Chrono Power (ultimate charge rate) */
	UFUNCTION(BlueprintPure)
	float GetChronoPower() const { return Stats.ChronoPower; }

	/** Tech Mage: Get Intelligence (skill damage) */
	UFUNCTION(BlueprintPure)
	float GetIntelligence() const { return Stats.Intelligence; }

	/** Chrome Sentinel: Get Resilience (max HP modifier) */
	UFUNCTION(BlueprintPure)
	float GetResilience() const { return Stats.Resilience; }

	/** Chrome Sentinel: Get Strength (melee damage) */
	UFUNCTION(BlueprintPure)
	float GetStrength() const { return Stats.Strength; }

	/** Neon Phantom: Get Mobility (speed) */
	UFUNCTION(BlueprintPure)
	float GetMobility() const { return Stats.Mobility; }

	/** Neon Phantom: Get Precision (critical damage) */
	UFUNCTION(BlueprintPure)
	float GetPrecision() const { return Stats.Precision; }

	/** Ghost Runner: Get Stealth (invisibility duration) */
	UFUNCTION(BlueprintPure)
	float GetStealth() const { return Stats.Stealth; }

	/** Ghost Runner: Get Tech (hack strength) */
	UFUNCTION(BlueprintPure)
	float GetTech() const { return Stats.Tech; }

	/** Solaris Warden: Get Restoration (healing amount) */
	UFUNCTION(BlueprintPure)
	float GetRestoration() const { return Stats.Restoration; }

	/** Solaris Warden: Get Radiance (ultimate strength) */
	UFUNCTION(BlueprintPure)
	float GetRadiance() const { return Stats.Radiance; }

protected:
	virtual void BeginPlay() override;

private:
	void ApplyClassModifiers();

	UPROPERTY()
	EClassType CurrentClass = EClassType::TechMage;

	UPROPERTY()
	FCharacterStats Stats;
};
