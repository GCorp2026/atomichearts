// Copyright 2026 Atomic Hearts Team

#pragma once

#include "CoreMinimal.h"
#include "EWeaponEnums.h"
#include "ExoticWeaponData.h"
#include "ExoticTraitDatabase.generated.h"

/**
 * Database of all exotic signature traits (50+).
 * Provides trait lookup by category and weapon slot compatibility.
 * Single static instance - no need for DataTable dependencies.
 */
UCLASS()
class ATOMICHEARTS_API UExoticTraitDatabase : public UObject
{
    GENERATED_BODY()

public:
    /** Get all traits for a specific weapon slot */
    UFUNCTION(BlueprintPure, Category = "Weapon|Exotic|Traits")
    static TArray<FExoticTraitData> GetTraitsForSlot(EWeaponSlot Slot);

    /** Get a trait by enum value */
    UFUNCTION(BlueprintPure, Category = "Weapon|Exotic|Traits")
    static FExoticTraitData GetTraitData(EExoticTrait Trait);

    /** Get all traits in a category */
    UFUNCTION(BlueprintPure, Category = "Weapon|Exotic|Traits")
    static TArray<FExoticTraitData> GetTraitsByCategory(ETraitCategory Category);

    /** Get trait name as string */
    UFUNCTION(BlueprintPure, Category = "Weapon|Exotic|Traits")
    static FString GetTraitName(EExoticTrait Trait);

    /** Get trait description */
    UFUNCTION(BlueprintPure, Category = "Weapon|Exotic|Traits")
    static FString GetTraitDescription(EExoticTrait Trait);

    /** Get all valid weapon slots for a trait */
    UFUNCTION(BlueprintPure, Category = "Weapon|Exotic|Traits")
    static TArray<EWeaponSlot> GetValidSlots(EExoticTrait Trait);

    /** Total number of defined traits */
    UFUNCTION(BlueprintPure, Category = "Weapon|Exotic|Traits")
    static int32 GetTraitCount() { return 53; }

private:
    /** Initialize the static trait registry */
    static void EnsureRegistryBuilt();

    /** Internal registry map */
    static TMap<EExoticTrait, FExoticTraitData>& GetRegistry();
};
