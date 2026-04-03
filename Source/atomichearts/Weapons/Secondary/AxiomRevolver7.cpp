// Copyright 2026 Atomic Hearts Team

#include "Weapons/Secondary/AxiomRevolver7.h"

AAxiomRevolver7::AAxiomRevolver7()
{
	WeaponName = FText::FromString("Axiom Revolver-7 Judge");
	WeaponDescription = FText::FromString("Six-shot revolving pistol. Corporate security standard issue.");
	WeaponSlot = EWeaponSlot::EWS_Secondary;
	AmmoType = EAmmoType::EAT_Ballistic;

	Stats.Damage = 55.f;
	Stats.FireRate = 0.5f;
	Stats.Range = 2800.f;
	Stats.Accuracy = 0.80f;
	Stats.HeadshotMultiplier = 2.4f;
	Stats.LegshotMultiplier = 0.5f;
	Stats.MaxRange = 4200.f;

	MagazineSize = 6;
	MaxReserveAmmo = 30;
	FireRate = 0.5f;

	NeonColor = FLinearColor(0.0f, 0.9f, 0.7f, 1.0f);
	Manufacturer = FText::FromString("Axiom Industries");
	ModelDesignation = FText::FromString("Revolver-7");
	TechRank = 2;
	AIEngagementRange = 1800.f;
	AIAccuracy = 0.75.f;
}

void AAxiomRevolver7::BeginPlay()
{
	Super::BeginPlay();
	CurrentAmmo = MagazineSize;
	ReserveAmmo = MaxReserveAmmo;
}
