#pragma once

#include "CoreMinimal.h"
#include "EArmorRarity.generated.h"

UENUM(BlueprintType)
enum class EArmorRarity : uint8
{
    Common      UMETA(DisplayName = "Common"),
    Uncommon    UMETA(DisplayName = "Uncommon"),
    Rare        UMETA(DisplayName = "Rare"),
    Legendary   UMETA(DisplayName = "Legendary"),
    Exotic      UMETA(DisplayName = "Exotic")
};
