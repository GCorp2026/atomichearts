// Copyright 2026 Atomic Hearts Team

#include "Weapons/Primary/ASolarisPulse11.h"

ASolarisPulse11::ASolarisPulse11()
{
	WeaponName = FText::FromString("Solaris Pulse-11 \"Eclipse\"");
	WeaponDescription = FText::FromString("Solar pulse rifle with maximum output. Blinding bursts of concentrated energy.");
	WeaponSlot = EWeaponSlot::EWS_Primary;
	AmmoType = EAmmoType::EAT_Energy;

	Stats.Damage = 32.f;
	Stats.FireRate = 0.14f;
	Stats.Range = 6500.f;
	Stats.Accuracy = 0.89f;
	Stats.HeadshotMultiplier = 2.5f;
	Stats.LegshotMultiplier = 0.5f;
	Stats.MaxRange = 10500.f;

	MagazineSize = 20;
	MaxReserveAmmo = 80;
	FireRate = 0.14f;

	NeonColor = FLinearColor(1.0f, 0.6f, 0.0f, 1.0f);
	EnergyColor = FLinearColor(1.0f, 0.5f, 0.1f, 1.0f);
	Manufacturer = FText::FromString("Solaris Energy Corp");
	ModelDesignation = FText::FromString("Pulse-11");
	TechRank = 2;
	AIEngagementRange = 4800.f;
	AIAccuracy = 0.86f;
}

void ASolarisPulse11::BeginPlay()
{
	Super::BeginPlay();
	CurrentAmmo = MagazineSize;
	ReserveAmmo = MaxReserveAmmo;
}
