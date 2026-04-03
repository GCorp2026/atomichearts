#pragma once

#include "CoreMinimal.h"
#include "FArmorStats.generated.h"

USTRUCT(BlueprintType)
struct FArmorStats
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Mobility = 10.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Resilience = 10.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Recovery = 10.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Discipline = 10.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Intellect = 10.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Strength = 10.f;

    FArmorStats() {}

    FArmorStats(float Mob, float Res, float Rec, float Dis, float Int, float Str)
        : Mobility(Mob), Resilience(Res), Recovery(Rec), Discipline(Dis), Intellect(Int), Strength(Str) {}

    float GetTotal() const
    {
        return Mobility + Resilience + Recovery + Discipline + Intellect + Strength;
    }
};
