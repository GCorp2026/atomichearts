// Copyright 2026 Atomic Hearts Team

#include "Weapons/Heavy/AGhostLMG.h"

AGhostLMG::AGhostLMG()
{
	WeaponName = FText::FromString("Ghost LMG-3 \"Ghost\"");
	WeaponDescription = FText::FromString("Ultra-silenced heavy machine gun. Ghost operatives use it for silent suppression.");
	WeaponSlot = EWeaponSlot::EWS_Heavy;
	AmmoType = EAmmoType::EAT_Ballistic;

	Stats.Damage = 15.f;
	Stats.FireRate = 0.065f;
	Stats.Range = 5000.f;
	Stats.Accuracy = 0.60f;
	Stats.HeadshotMultiplier = 1.8f;
	Stats.LegshotMultiplier = 0.5f;
	Stats.MaxRange = 7500.f;

	MagazineSize = 90;
	MaxReserveAmmo = 180;
	FireRate = 0.065f;

	SuppressionRadius = 420.f;

	NeonColor = FLinearColor(0.0f, 0.9f, 0.4f, 1.0f);
	Manufacturer = FText::FromString("Ghost Collective");
	ModelDesignation = FText::FromString("LMG-3");
	TechRank = 2;
	AIEngagementRange = 3800.f;
	AIAccuracy = 0.55f;
}

void AGhostLMG::BeginPlay()
{
	Super::BeginPlay();
	CurrentAmmo = MagazineSize;
	ReserveAmmo = MaxReserveAmmo;
}
