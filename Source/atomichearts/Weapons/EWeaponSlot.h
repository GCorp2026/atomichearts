// Copyright 2026 Atomic Hearts Team

#pragma once

#include "CoreMinimal.h"
#include "EWeaponSlot.generated.h"

UENUM(BlueprintType)
enum class EWeaponSlot : uint8
{
	Primary_AR   UMETA(DisplayName = "Primary AR"),
	Primary_PR   UMETA(DisplayName = "Primary Pulse Rifle"),
	Primary_SR   UMETA(DisplayName = "Primary Scout Rifle"),
	Secondary_HC UMETA(DisplayName = "Secondary Hand Cannon"),
	Secondary_SMG UMETA(DisplayName = "Secondary SMG"),
	Secondary_SG UMETA(DisplayName = "Secondary Shotgun"),
	Heavy_RL     UMETA(DisplayName = "Heavy Rocket Launcher"),
	Heavy_LMG    UMETA(DisplayName = "Heavy LMG"),
	Heavy_SW     UMETA(DisplayName = "Heavy Sword"),
	Heavy_GL     UMETA(DisplayName = "Heavy Grenade Launcher"),

	Max UMETA(Hidden)
};
