// Copyright 2026 Atomic Hearts Team

#include "Weapons/Primary/AGhostSR5.h"

AGhostSR5::AGhostSR5()
{
	WeaponName = FText::FromString("Ghost SR-5 \"Phantom\"");
	WeaponDescription = FText::FromString("Stealth sniper rifle. Ghost operatives strike before targets realize.");
	WeaponSlot = EWeaponSlot::EWS_Primary;
	AmmoType = EAmmoType::EAT_Ballistic;

	Stats.Damage = 80.f;
	Stats.FireRate = 0.6f;
	Stats.Range = 11000.f;
	Stats.Accuracy = 0.98f;
	Stats.HeadshotMultiplier = 3.5f;
	Stats.LegshotMultiplier = 0.5f;
	Stats.MaxRange = 16000.f;

	MagazineSize = 5;
	MaxReserveAmmo = 20;
	FireRate = 0.6f;

	NeonColor = FLinearColor(0.3f, 0.0f, 0.5f, 1.0f);
	Manufacturer = FText::FromString("Ghost Networks");
	ModelDesignation = FText::FromString("SR-5");
	TechRank = 2;
	AIEngagementRange = 8000.f;
	AIAccuracy = 0.95f;
}

void AGhostSR5::BeginPlay()
{
	Super::BeginPlay();
	CurrentAmmo = MagazineSize;
	ReserveAmmo = MaxReserveAmmo;
}
