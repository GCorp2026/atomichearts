// Copyright 2026 Atomic Hearts Team

#include "Weapons/Primary/ANeonSMG8.h"

ANeonSMG8::ANeonSMG8()
{
	WeaponName = FText::FromString("Neon SMG-8 \"Viper\"");
	WeaponDescription = FText::FromString("Lightning-fast submachine gun. Unloads rounds in a blur of neon tracers.");
	WeaponSlot = EWeaponSlot::EWS_Primary;
	AmmoType = EAmmoType::EAT_Ballistic;

	Stats.Damage = 12.f;
	Stats.FireRate = 0.03f;
	Stats.Range = 2000.f;
	Stats.Accuracy = 0.62f;
	Stats.HeadshotMultiplier = 1.8f;
	Stats.LegshotMultiplier = 0.5f;
	Stats.MaxRange = 3500.f;

	MagazineSize = 50;
	MaxReserveAmmo = 200;
	FireRate = 0.03f;

	NeonColor = FLinearColor(1.0f, 0.2f, 0.6f, 1.0f);
	Manufacturer = FText::FromString("Neon Tech Labs");
	ModelDesignation = FText::FromString("SMG-8");
	TechRank = 1;
	AIEngagementRange = 1200.f;
	AIAccuracy = 0.58f;
}

void ANeonSMG8::BeginPlay()
{
	Super::BeginPlay();
	CurrentAmmo = MagazineSize;
	ReserveAmmo = MaxReserveAmmo;
}
