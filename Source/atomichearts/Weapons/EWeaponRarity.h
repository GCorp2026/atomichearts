// Copyright 2026 Atomic Hearts Team

#pragma once

#include "CoreMinimal.h"
#include "EWeaponRarity.generated.h"

UENUM(BlueprintType)
enum class EWeaponRarity : uint8
{
	Common     UMETA(DisplayName = "Common"),
	Uncommon   UMETA(DisplayName = "Uncommon"),
	Rare       UMETA(DisplayName = "Rare"),
	Legendary  UMETA(DisplayName = "Legendary"),
	Exotic     UMETA(DisplayName = "Exotic"),

	Max UMETA(Hidden)
};
