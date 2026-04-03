// Copyright 2026 Atomic Hearts Team

#include "Weapons/Secondary/AxiomHC12.h"

AAxiomHC12::AAxiomHC12()
{
	WeaponName = FText::FromString("Axiom HC-12 Enforcer");
	WeaponDescription = FText::FromString("Overclocked heavy pistol. Devastating stopping power for corporate enforcers.");
	WeaponSlot = EWeaponSlot::EWS_Secondary;
	AmmoType = EAmmoType::EAT_Ballistic;

	Stats.Damage = 72.f;
	Stats.FireRate = 0.7f;
	Stats.Range = 2200.f;
	Stats.Accuracy = 0.68f;
	Stats.HeadshotMultiplier = 2.6f;
	Stats.LegshotMultiplier = 0.5f;
	Stats.MaxRange = 3800.f;

	MagazineSize = 8;
	MaxReserveAmmo = 40;
	FireRate = 0.7f;

	NeonColor = FLinearColor(0.0f, 0.8f, 1.0f, 1.0f);
	Manufacturer = FText::FromString("Axiom Industries");
	ModelDesignation = FText::FromString("HC-12");
	TechRank = 2;
	AIEngagementRange = 1200.f;
	AIAccuracy = 0.70f;
}

void AAxiomHC12::BeginPlay()
{
	Super::BeginPlay();
	CurrentAmmo = MagazineSize;
	ReserveAmmo = MaxReserveAmmo;
}
