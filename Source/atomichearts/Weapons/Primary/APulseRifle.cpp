// Copyright 2026 Atomic Hearts Team

#include "Weapons/Primary/APulseRifle.h"

APulseRifle::APulseRifle()
{
	WeaponName = FText::FromString("Neon PR-3");
	WeaponDescription = FText::FromString("Pulse rifle with energy rounds. High accuracy with moderate stopping power.");
	WeaponSlot = EWeaponSlot::EWS_Primary;
	AmmoType = EAmmoType::EAT_Energy;

	Stats.Damage = 28.f;
	Stats.FireRate = 0.15f;
	Stats.Range = 5500.f;
	Stats.Accuracy = 0.88f;
	Stats.HeadshotMultiplier = 2.5f;
	Stats.LegshotMultiplier = 0.5f;
	Stats.MaxRange = 9000.f;

	MagazineSize = 25;
	MaxReserveAmmo = 100;
	FireRate = 0.15f;

	NeonColor = FLinearColor(0.0f, 1.0f, 0.85f, 1.0f);
	EnergyColor = FLinearColor(0.0f, 0.8f, 1.0f, 1.0f);
	Manufacturer = FText::FromString("Neon Tech Labs");
	ModelDesignation = FText::FromString("PR-3");
	TechRank = 1;
	AIEngagementRange = 4000.f;
	AIAccuracy = 0.82f;
}

void APulseRifle::BeginPlay()
{
	Super::BeginPlay();
	CurrentAmmo = MagazineSize;
	ReserveAmmo = MaxReserveAmmo;
}
