// Copyright 2024 Destiny Cyberpunk

#include "UClassAbilityComponent.h"
#include "EClassType.h"
#include "GameplayAbility.h"
#include "AbilitySystemComponent.h"
#include "AAtomichartsCharacter.h"

UClassAbilityComponent::UClassAbilityComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	AbilitySlots.SetNum(4);
	Cooldowns.SetNum(4);
}

void UClassAbilityComponent::BeginPlay()
{
	Super::BeginPlay();
	OwnerActor = GetOwner();
	ConfigureAbilitiesForClass();
}

void UClassAbilityComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Tick cooldowns
	for (int32 i = 0; i < Cooldowns.Num(); ++i)
	{
		if (Cooldowns[i].RemainingTime > 0.f)
		{
			Cooldowns[i].RemainingTime -= DeltaTime;
			if (Cooldowns[i].RemainingTime < 0.f)
				Cooldowns[i].RemainingTime = 0.f;
		}
	}

	// Passive ultimate charge accumulation
	if (CurrentClass == EClassType::TechMage)
	{
		ChargeAccumulator += DeltaTime * 0.8f; // Chrono Power
	}
	else if (CurrentClass == EClassType::SolarisWarden)
	{
		ChargeAccumulator += DeltaTime * 1.0f; // Radiance
	}
	else
	{
		ChargeAccumulator += DeltaTime * 0.5f;
	}

	float UltimateThreshold = 100.f;
	if (ChargeAccumulator >= UltimateThreshold)
	{
		ChargeAccumulator = UltimateThreshold;
	}
}

void UClassAbilityComponent::SetClass(EClassType NewClass)
{
	CurrentClass = NewClass;
	ConfigureAbilitiesForClass();
	GrantAbilitiesToActor();
}

void UClassAbilityComponent::ConfigureAbilitiesForClass()
{
	// Reset abilities
	for (auto& Slot : AbilitySlots)
	{
		Slot = FAbilityDefinition();
	}

	switch (CurrentClass)
	{
	case EClassType::TechMage:
		// Time Slow, Chrono Trap, Phase Shift, Time Stop (Ultimate)
		AbilitySlots[0] = { EAbilityType::TimeSlow, 8.f, 20.f };
		AbilitySlots[1] = { EAbilityType::ChronoTrap, 12.f, 30.f };
		AbilitySlots[2] = { EAbilityType::PhaseShift, 10.f, 0.f };
		AbilitySlots[3] = { EAbilityType::TimeStop, 180.f, 0.f };
		break;

	case EClassType::ChromeSentinel:
		// Rally Shield, Ground Pound, Overshield, Barricade (Ultimate)
		AbilitySlots[0] = { EAbilityType::RallyShield, 15.f, 0.f };
		AbilitySlots[1] = { EAbilityType::GroundPound, 10.f, 0.f };
		AbilitySlots[2] = { EAbilityType::Overshield, 20.f, 0.f };
		AbilitySlots[3] = { EAbilityType::Barricade, 90.f, 0.f };
		break;

	case EClassType::NeonPhantom:
		// Fan the Hammer, Marked for Death, Gun Kata, Dodge (Ultimate is Dodge here)
		AbilitySlots[0] = { EAbilityType::FanTheHammer, 6.f, 0.f };
		AbilitySlots[1] = { EAbilityType::MarkedForDeath, 15.f, 0.f };
		AbilitySlots[2] = { EAbilityType::GunKata, 8.f, 0.f };
		AbilitySlots[3] = { EAbilityType::Dodge, 30.f, 0.f };
		break;

	case EClassType::GhostRunner:
		// Scout Drone, Blink, EMP Burst, Vanish (Ultimate)
		AbilitySlots[0] = { EAbilityType::ScoutDrone, 20.f, 0.f };
		AbilitySlots[1] = { EAbilityType::Blink, 8.f, 0.f };
		AbilitySlots[2] = { EAbilityType::EMPBurst, 15.f, 0.f };
		AbilitySlots[3] = { EAbilityType::Vanish, 120.f, 0.f };
		break;

	case EClassType::SolarisWarden:
		// Solar Grenade, Revival, Solar Flare, Healing Rift (Ultimate)
		AbilitySlots[0] = { EAbilityType::SolarGrenade, 10.f, 0.f };
		AbilitySlots[1] = { EAbilityType::Revival, 45.f, 0.f };
		AbilitySlots[2] = { EAbilityType::SolarFlare, 12.f, 0.f };
		AbilitySlots[3] = { EAbilityType::HealingRift, 90.f, 0.f };
		break;
	}
}

bool UClassAbilityComponent::ActivateAbility(int32 SlotIndex)
{
	if (SlotIndex < 0 || SlotIndex >= AbilitySlots.Num())
		return false;

	if (!IsAbilityReady(SlotIndex))
		return false;

	const FAbilityDefinition& Def = AbilitySlots[SlotIndex];
	if (Def.AbilityType == EAbilityType::None)
		return false;

	// Execute ability effect based on type
	AActor* Owner = GetOwner();
	if (!Owner)
		return false;

	// Notify character to play animation / spawn effects
	if (AAAtomichartsCharacter* Char = Cast<AAAtomichartsCharacter>(Owner))
	{
		Char->OnAbilityActivated(Def.AbilityType);
	}

	StartCooldown(SlotIndex, Def.Cooldown);
	return true;
}

bool UClassAbilityComponent::ActivateUltimate()
{
	return ActivateAbility(3);
}

bool UClassAbilityComponent::IsAbilityReady(int32 SlotIndex) const
{
	if (SlotIndex < 0 || SlotIndex >= Cooldowns.Num())
		return false;
	return Cooldowns[SlotIndex].IsReady();
}

float UClassAbilityComponent::GetCooldownProgress(int32 SlotIndex) const
{
	if (SlotIndex < 0 || SlotIndex >= Cooldowns.Num())
		return 0.f;
	return Cooldowns[SlotIndex].GetProgress();
}

EAbilityType UClassAbilityComponent::GetAbilityType(int32 SlotIndex) const
{
	if (SlotIndex < 0 || SlotIndex >= AbilitySlots.Num())
		return EAbilityType::None;
	return AbilitySlots[SlotIndex].AbilityType;
}

void UClassAbilityComponent::StartCooldown(int32 SlotIndex, float Duration)
{
	if (SlotIndex < 0 || SlotIndex >= Cooldowns.Num())
		return;
	Cooldowns[SlotIndex].TotalTime = Duration;
	Cooldowns[SlotIndex].RemainingTime = Duration;
}

void UClassAbilityComponent::ReduceCooldowns(float Amount)
{
	for (auto& CD : Cooldowns)
	{
		CD.RemainingTime = FMath::Max(0.f, CD.RemainingTime - Amount);
	}
}

void UClassAbilityComponent::GrantAbilitiesToActor()
{
	// Placeholder: In full GAS setup, this would give abilities via AbilitySystemComponent
}
