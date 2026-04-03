// Copyright 2026 Atomic Hearts Team

#include "Weapons/Primary/AAxiomPulse3.h"

AAxiomPulse3::AAxiomPulse3()
{
	WeaponName = FText::FromString("Axiom Pulse-3 \"Mainframe\"");
	WeaponDescription = FText::FromString("Smart-pulse rifle with AI-assisted targeting. Locks onto threats for precise energy bursts.");
	WeaponSlot = EWeaponSlot::EWS_Primary;
	AmmoType = EAmmoType::EAT_Energy;

	Stats.Damage = 24.f;
	Stats.FireRate = 0.12f;
	Stats.Range = 6000.f;
	Stats.Accuracy = 0.90f;
	Stats.HeadshotMultiplier = 2.3f;
	Stats.LegshotMultiplier = 0.5f;
	Stats.MaxRange = 10000.f;

	MagazineSize = 22;
	MaxReserveAmmo = 88;
	FireRate = 0.12f;

	NeonColor = FLinearColor(0.0f, 1.0f, 0.6f, 1.0f);
	EnergyColor = FLinearColor(0.0f, 0.9f, 0.4f, 1.0f);
	Manufacturer = FText::FromString("Axiom Industries");
	ModelDesignation = FText::FromString("Pulse-3");
	TechRank = 2;
	AIEngagementRange = 4500.f;
	AIAccuracy = 0.88f;
}

void AAxiomPulse3::BeginPlay()
{
	Super::BeginPlay();
	CurrentAmmo = MagazineSize;
	ReserveAmmo = MaxReserveAmmo;
}
