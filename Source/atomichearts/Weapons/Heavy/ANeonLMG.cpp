// Copyright 2026 Atomic Hearts Team

#include "Weapons/Heavy/ANeonLMG.h"

ANeonLMG::ANeonLMG()
{
	WeaponName = FText::FromString("Neon LMG-4 \"Street\"");
	WeaponDescription = FText::FromString("Cobbled-together LMG. Neon pink muzzle flashes and jury-rigged feed system.");
	WeaponSlot = EWeaponSlot::EWS_Heavy;
	AmmoType = EAmmoType::EAT_Ballistic;

	Stats.Damage = 14.f;
	Stats.FireRate = 0.07f;
	Stats.Range = 4000.f;
	Stats.Accuracy = 0.48f;
	Stats.HeadshotMultiplier = 1.7f;
	Stats.LegshotMultiplier = 0.5f;
	Stats.MaxRange = 6000.f;

	MagazineSize = 80;
	MaxReserveAmmo = 160;
	FireRate = 0.07f;

	SuppressionRadius = 380.f;

	NeonColor = FLinearColor(1.0f, 0.0f, 0.8f, 1.0f);
	Manufacturer = FText::FromString("Neon Syndicate");
	ModelDesignation = FText::FromString("LMG-4");
	TechRank = 0;
	AIEngagementRange = 3500.f;
	AIAccuracy = 0.42f;
}

void ANeonLMG::BeginPlay()
{
	Super::BeginPlay();
	CurrentAmmo = MagazineSize;
	ReserveAmmo = MaxReserveAmmo;
}
