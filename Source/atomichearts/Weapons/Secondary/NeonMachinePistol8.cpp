// Copyright 2026 Atomic Hearts Team

#include "Weapons/Secondary/NeonMachinePistol8.h"

ANeonMachinePistol8::ANeonMachinePistol8()
{
	WeaponName = FText::FromString("Neon MachinePistol-8 FullAuto");
	WeaponDescription = FText::FromString("Full-auto guncaster pistol. Spray and pray at its finest.");
	WeaponSlot = EWeaponSlot::EWS_Secondary;
	AmmoType = EAmmoType::EAT_Ballistic;

	Stats.Damage = 10.f;
	Stats.FireRate = 0.03f;
	Stats.Range = 1500.f;
	Stats.Accuracy = 0.45f;
	Stats.HeadshotMultiplier = 1.5f;
	Stats.LegshotMultiplier = 0.5f;
	Stats.MaxRange = 2500.f;

	MagazineSize = 25;
	MaxReserveAmmo = 125;
	FireRate = 0.03f;

	NeonColor = FLinearColor(1.0f, 0.2f, 0.2f, 1.0f);
	Manufacturer = FText::FromString("Neon Arms");
	ModelDesignation = FText::FromString("MachinePistol-8");
	TechRank = 1;
	AIEngagementRange = 800.f;
	AIAccuracy = 0.40.f;
}

void ANeonMachinePistol8::BeginPlay()
{
	Super::BeginPlay();
	CurrentAmmo = MagazineSize;
	ReserveAmmo = MaxReserveAmmo;
}
