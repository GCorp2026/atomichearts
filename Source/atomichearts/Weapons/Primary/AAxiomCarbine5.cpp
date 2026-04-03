// Copyright 2026 Atomic Hearts Team

#include "Weapons/Primary/AAxiomCarbine5.h"

AAxiomCarbine5::AAxiomCarbine5()
{
	WeaponName = FText::FromString("Axiom Carbine-5");
	WeaponDescription = FText::FromString("Compact automatic carbine. Reliable in tight spaces with excellent accuracy.");
	WeaponSlot = EWeaponSlot::EWS_Primary;
	AmmoType = EAmmoType::EAT_Ballistic;

	Stats.Damage = 20.f;
	Stats.FireRate = 0.07f;
	Stats.Range = 3000.f;
	Stats.Accuracy = 0.86f;
	Stats.HeadshotMultiplier = 2.0f;
	Stats.LegshotMultiplier = 0.5f;
	Stats.MaxRange = 5000.f;

	MagazineSize = 28;
	MaxReserveAmmo = 112;
	FireRate = 0.07f;

	NeonColor = FLinearColor(0.0f, 0.85f, 0.35f, 1.0f);
	Manufacturer = FText::FromString("Axiom Industries");
	ModelDesignation = FText::FromString("Carbine-5");
	TechRank = 1;
	AIEngagementRange = 2000.f;
	AIAccuracy = 0.82f;
}

void AAxiomCarbine5::BeginPlay()
{
	Super::BeginPlay();
	CurrentAmmo = MagazineSize;
	ReserveAmmo = MaxReserveAmmo;
}
