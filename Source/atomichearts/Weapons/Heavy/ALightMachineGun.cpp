// Copyright 2026 Atomic Hearts Team

#include "Weapons/Heavy/ALightMachineGun.h"

ALightMachineGun::ALightMachineGun()
{
	WeaponName = FText::FromString("Axiom LMG-7");
	WeaponDescription = FText::FromString("Heavy machine gun built for suppression. High capacity drum magazine with sustained fire.");
	WeaponSlot = EWeaponSlot::EWS_Heavy;
	AmmoType = EAmmoType::EAT_Ballistic;

	Stats.Damage = 16.f;
	Stats.FireRate = 0.06f;
	Stats.Range = 5000.f;
	Stats.Accuracy = 0.55f;
	Stats.HeadshotMultiplier = 1.8f;
	Stats.LegshotMultiplier = 0.5f;
	Stats.MaxRange = 8000.f;

	MagazineSize = 100;
	MaxReserveAmmo = 200;
	FireRate = 0.06f;

	SuppressionRadius = 400.f;

	NeonColor = FLinearColor(0.8f, 0.6f, 0.0f, 1.0f);
	Manufacturer = FText::FromString("Axiom Industries");
	ModelDesignation = FText::FromString("LMG-7");
	TechRank = 1;
	AIEngagementRange = 4000.f;
	AIAccuracy = 0.50f;
}

void ALightMachineGun::BeginPlay()
{
	Super::BeginPlay();
	CurrentAmmo = MagazineSize;
	ReserveAmmo = MaxReserveAmmo;
}
