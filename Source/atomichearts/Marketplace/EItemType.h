#pragma once
#include "CoreMinimal.h"
#include "EItemType.generated.h"

UENUM(BlueprintType)
enum class EItemType : uint8 {
    None    UMETA(DisplayName = "None"),
    Weapon  UMETA(DisplayName = "Weapon"),
    Armor   UMETA(DisplayName = "Armor")
};
