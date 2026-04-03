#pragma once

#include "CoreMinimal.h"
#include "AtomichartsTypes.generated.h"

UENUM(BlueprintType)
enum class EMatchState : uint8
{
    Waiting,
    Starting,
    InProgress,
    Finished,
    Overtime
};

UENUM(BlueprintType)
enum class EActivityType : uint8
{
    Patrol,
    Strike,
    Raid,
    Crucible,
    Gambit
};

UENUM(BlueprintType)
enum class EFaction : uint8
{
    Vanguard,
    Renegades,
    Collectors,
    FirstLight
};

UENUM(BlueprintType)
enum class EFactionRank : uint8
{
    Neutral,
    Initiate,
    Veteran,
    Master,
    Legendary
};
