// Copyright 2026 Atomic Hearts Team

#include "Weapons/Primary/AAxiomAR9.h"

AAxiomAR9::AAxiomAR9()
{
	WeaponName = FText::FromString("Axiom AR-9 \"Overkill\"");
	WeaponDescription = FText::FromString("Full-auto assault rifle built for urban combat. Devastating at close range.");
	WeaponSlot = EWeaponSlot::EWS_Primary;
	AmmoType = EAmmoType::EAT_Ballistic;

	Stats.Damage = 18.f;
	Stats.FireRate = 0.05f;
	Stats.Range = 3500.f;
	Stats.Accuracy = 0.72f;
	Stats.HeadshotMultiplier = 2.0f;
	Stats.LegshotMultiplier = 0.5f;
	Stats.MaxRange = 6000.f;

	MagazineSize = 40;
	MaxReserveAmmo = 160;
	FireRate = 0.05f;

	NeonColor = FLinearColor(0.0f, 0.95f, 0.4f, 1.0f);
	Manufacturer = FText::FromString("Axiom Industries");
	ModelDesignation = FText::FromString("AR-9");
	TechRank = 1;
	AIEngagementRange = 2500.f;
	AIAccuracy = 0.70f;
}

void AAxiomAR9::BeginPlay()
{
	Super::BeginPlay();
	CurrentAmmo = MagazineSize;
	ReserveAmmo = MaxReserveAmmo;
}
