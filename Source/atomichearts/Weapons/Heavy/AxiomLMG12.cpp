// Copyright 2026 Atomic Hearts Team

#include "Weapons/Heavy/AxiomLMG12.h"

CAxiomLMG12::CAxiomLMG12()
{
	WeaponName = FText::FromString("Axiom LMG-12 \"Suppressor\"");
	WeaponDescription = FText::FromString("Extended barrel heavy machine gun. Devastating sustained fire with massive suppression radius.");
	WeaponSlot = EWeaponSlot::EWS_Heavy;
	AmmoType = EAmmoType::EAT_Ballistic;

	Stats.Damage = 18.f;
	Stats.FireRate = 0.055f;
	Stats.Range = 6000.f;
	Stats.Accuracy = 0.50f;
	Stats.HeadshotMultiplier = 1.8f;
	Stats.LegshotMultiplier = 0.5f;
	Stats.MaxRange = 9000.f;

	MagazineSize = 120;
	MaxReserveAmmo = 240;
	FireRate = 0.055f;

	SuppressionRadius = 500.f;

	NeonColor = FLinearColor(0.9f, 0.7f, 0.1f, 1.0f);
	Manufacturer = FText::FromString("Axiom Industries");
	ModelDesignation = FText::FromString("LMG-12");
	TechRank = 1;
	AIEngagementRange = 4500.f;
	AIAccuracy = 0.45f;
}

void CAxiomLMG12::BeginPlay()
{
	Super::BeginPlay();
	CurrentAmmo = MagazineSize;
	ReserveAmmo = MaxReserveAmmo;
}
