// Copyright 2026 Atomic Hearts Team
#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FWeaponProgressionData.h"
#include "UWeaponProgressionComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnWeaponLevelUp, int32, NewLevel, int32, XPAwarded, const TArray<FWeaponPerk>&, NewPerks, float, DamageBonus);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnRarityUpgrade, EWeaponRarity, OldRarity, EWeaponRarity, NewRarity, int32, XPCost);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnXPAdded, int32, Amount, int32, NewTotalXP);

UCLASS(ClassGroup=(Atomichearts), meta=(BlueprintSpawnableComponent))
class ATOMICHEARTS_API UWeaponProgressionComponent : public UActorComponent {
    GENERATED_BODY()

public:
    UWeaponProgressionComponent();

    /** Add XP from any source (kill, headshot, assist, etc.) */
    UFUNCTION(BlueprintCallable)
    void AddXP(int32 Amount, bool bIsHeadshot = false);

    /** Attempt to upgrade rarity if enough XP available */
    UFUNCTION(BlueprintCallable)
    bool TryRarityUpgrade();

    /** Fully reset progression */
    UFUNCTION(BlueprintCallable)
    void ResetProgression();

    UFUNCTION(BlueprintPure)
    int32 GetXPForNextLevel() const;

    UFUNCTION(BlueprintPure)
    float GetLevelProgress() const; // 0.0 - 1.0

    UFUNCTION(BlueprintPure)
    bool CanUpgradeRarity() const;

    UFUNCTION(BlueprintPure)
    FWeaponProgressionState GetState() const { return State; }

    UPROPERTY(BlueprintAssignable)
    FOnWeaponLevelUp OnWeaponLevelUp;

    UPROPERTY(BlueprintAssignable)
    FOnRarityUpgrade OnRarityUpgrade;

    UPROPERTY(BlueprintAssignable)
    FOnXPAdded OnXPAdded;

protected:
    void BeginPlay() override;
    void LevelUpIfPossible();

    /** Get XP needed for next level from table */
    int32 GetXPThresholdForLevel(int32 Level) const;

    /** Unlock a perk at the given level */
    void UnlockPerkForLevel(int32 Level);

    /** Rarity upgrade table */
    UPROPERTY(EditDefaultsOnly, Category="Progression")
    TArray<FRarityUpgradePath> RarityUpgradePaths;

    UPROPERTY(EditDefaultsOnly, Category="Progression")
    int32 BaseXPPerKill = 100;

    UPROPERTY(EditDefaultsOnly, Category="Progression")
    int32 HeadshotXPBonus = 50;

    UPROPERTY(EditDefaultsOnly, Category="Progression")
    int32 MaxLevel = 50;

    UPROPERTY(EditAnywhere, Category="Progression")
    FWeaponProgressionState State;
};
