// Copyright 2026 Atomic Hearts Team

#include "Weapons/Heavy/ASolarisLMG.h"

ASolarisLMG::ASolarisLMG()
{
	WeaponName = FText::FromString("Solaris LMG-8 \"Flare\"");
	WeaponDescription = FText::FromString("Solar-heated rounds. Each hit has a chance to ignite targets for bonus burn damage.");
	WeaponSlot = EWeaponSlot::EWS_Heavy;
	AmmoType = EAmmoType::EAT_Plasma;

	Stats.Damage = 17.f;
	Stats.FireRate = 0.06f;
	Stats.Range = 5500.f;
	Stats.Accuracy = 0.57f;
	Stats.HeadshotMultiplier = 1.85f;
	Stats.LegshotMultiplier = 0.5f;
	Stats.MaxRange = 8200.f;

	MagazineSize = 100;
	MaxReserveAmmo = 200;
	FireRate = 0.06f;

	SuppressionRadius = 480.f;
	IgniteChance = 0.25f;

	NeonColor = FLinearColor(1.0f, 0.5f, 0.0f, 1.0f);
	EnergyColor = FLinearColor(1.0f, 0.8f, 0.1f, 1.0f);
	Manufacturer = FText::FromString("Solaris Defense");
	ModelDesignation = FText::FromString("LMG-8");
	TechRank = 1;
	AIEngagementRange = 4200.f;
	AIAccuracy = 0.52f;
}

void ASolarisLMG::BeginPlay()
{
	Super::BeginPlay();
	CurrentAmmo = MagazineSize;
	ReserveAmmo = MaxReserveAmmo;
}
