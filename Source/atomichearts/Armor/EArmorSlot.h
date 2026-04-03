#pragma once

#include "CoreMinimal.h"
#include "EArmorSlot.generated.h"

UENUM(BlueprintType)
enum class EArmorSlot : uint8
{
    Helmet      UMETA(DisplayName = "Helmet"),
    Gauntlets   UMETA(DisplayName = "Gauntlets"),
    Chest       UMETA(DisplayName = "Chest"),
    Legs        UMETA(DisplayName = "Legs"),
    ClassItem   UMETA(DisplayName = "Class Item"),
    Mark        UMETA(DisplayName = "Mark")
};
