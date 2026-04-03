// Copyright 2026 Atomic Hearts Team

#include "Weapons/Primary/AGhostPulse9.h"

AGhostPulse9::AGhostPulse9()
{
	WeaponName = FText::FromString("Ghost Pulse-9 \"Glitch\"");
	WeaponDescription = FText::FromString("Jammer pulse rifle. Disrupts enemy tech and neural implants on impact.");
	WeaponSlot = EWeaponSlot::EWS_Primary;
	AmmoType = EAmmoType::EAT_Energy;

	Stats.Damage = 20.f;
	Stats.FireRate = 0.1f;
	Stats.Range = 5000.f;
	Stats.Accuracy = 0.87f;
	Stats.HeadshotMultiplier = 2.2f;
	Stats.LegshotMultiplier = 0.5f;
	Stats.MaxRange = 8000.f;

	MagazineSize = 28;
	MaxReserveAmmo = 112;
	FireRate = 0.1f;

	NeonColor = FLinearColor(0.5f, 0.0f, 0.8f, 1.0f);
	EnergyColor = FLinearColor(0.7f, 0.0f, 1.0f, 1.0f);
	Manufacturer = FText::FromString("Ghost Networks");
	ModelDesignation = FText::FromString("Pulse-9");
	TechRank = 2;
	AIEngagementRange = 3500.f;
	AIAccuracy = 0.85f;
}

void AGhostPulse9::BeginPlay()
{
	Super::BeginPlay();
	CurrentAmmo = MagazineSize;
	ReserveAmmo = MaxReserveAmmo;
}
