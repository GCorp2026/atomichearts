// Copyright 2026 Atomic Hearts Team

#include "Weapons/Primary/AAxiomAR12.h"

AAxiomAR12::AAxiomAR12()
{
	WeaponName = FText::FromString("Axiom AR-12 \"Protocol\"");
	WeaponDescription = FText::FromString("Burst-fire assault rifle. Three-round burst delivers precise, lethal impact.");
	WeaponSlot = EWeaponSlot::EWS_Primary;
	AmmoType = EAmmoType::EAT_Ballistic;

	Stats.Damage = 26.f;
	Stats.FireRate = 0.18f;
	Stats.Range = 5000.f;
	Stats.Accuracy = 0.85f;
	Stats.HeadshotMultiplier = 2.2f;
	Stats.LegshotMultiplier = 0.5f;
	Stats.MaxRange = 8500.f;

	MagazineSize = 30;
	MaxReserveAmmo = 120;
	FireRate = 0.18f;

	NeonColor = FLinearColor(0.1f, 1.0f, 0.5f, 1.0f);
	Manufacturer = FText::FromString("Axiom Industries");
	ModelDesignation = FText::FromString("AR-12");
	TechRank = 1;
	AIEngagementRange = 4000.f;
	AIAccuracy = 0.80f;
}

void AAxiomAR12::BeginPlay()
{
	Super::BeginPlay();
	CurrentAmmo = MagazineSize;
	ReserveAmmo = MaxReserveAmmo;
}
