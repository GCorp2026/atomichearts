// Copyright 2026 Atomic Hearts Team
#include "Progression/UWeaponProgressionComponent.h"
#include "Kismet/KismetMathLibrary.h"

UWeaponProgressionComponent::UWeaponProgressionComponent() {
    PrimaryComponentTick.bCanEverTick = false;
}

void UWeaponProgressionComponent::BeginPlay() {
    Super::BeginPlay();
}

int32 UWeaponProgressionComponent::GetXPThresholdForLevel(int32 Level) const {
    // XP curve: level N needs roughly N*100 XP cumulative
    return Level * (Level + 1) * 50;
}

int32 UWeaponProgressionComponent::GetXPForNextLevel() const {
    return GetXPThresholdForLevel(State.CurrentLevel + 1);
}

float UWeaponProgressionComponent::GetLevelProgress() const {
    int32 CurrentThreshold = GetXPThresholdForLevel(State.CurrentLevel);
    int32 NextThreshold = GetXPThresholdForLevel(State.CurrentLevel + 1);
    if (NextThreshold <= CurrentThreshold) return 1.f;
    float Progress = float(State.CurrentXP - CurrentThreshold) /
                     float(NextThreshold - CurrentThreshold);
    return FMath::Clamp(Progress, 0.f, 1.f);
}

void UWeaponProgressionComponent::AddXP(int32 Amount, bool bIsHeadshot) {
    if (State.CurrentLevel >= MaxLevel) return;

    if (bIsHeadshot) {
        Amount = FMath::CeilToInt(Amount * State.HeadshotXPMultiplier);
        State.Headshots++;
    }

    // #3: Increment kill count on XP gain
    State.TotalKills++;
    State.CurrentXP += Amount;
    OnXPAdded.Broadcast(Amount, State.CurrentXP);

    UE_LOG(LogTemp, Log, TEXT("AddXP: +%d (Headshot=%d) TotalXP=%d Level=%d"),
           Amount, bIsHeadshot, State.CurrentXP, State.CurrentLevel);

    LevelUpIfPossible();
}

void UWeaponProgressionComponent::LevelUpIfPossible() {
    while (State.CurrentLevel < MaxLevel && State.CurrentXP >= GetXPForNextLevel()) {
        State.CurrentLevel++;

        TArray<FWeaponPerk> NewPerks;
        float DamageBonus = 0.f;

        // Unlock perk at this level (every 5 levels)
        if (State.CurrentLevel % 5 == 0) {
            UnlockPerkForLevel(State.CurrentLevel);
            if (State.UnlockedPerks.Num() > 0) {
                NewPerks.Add(State.UnlockedPerks.Last());
            }
        }

        // Small passive bonuses every level
        DamageBonus = State.CurrentLevel * 0.5f;

        UE_LOG(LogTemp, Log, TEXT("LevelUp! NewLevel=%d TotalPerks=%d"),
               State.CurrentLevel, State.UnlockedPerks.Num());

        OnWeaponLevelUp.Broadcast(State.CurrentLevel, State.CurrentXP, NewPerks, DamageBonus);
    }
}

void UWeaponProgressionComponent::UnlockPerkForLevel(int32 Level) {
    // Generate a unique perk based on level
    FWeaponPerk Perk;
    Perk.PerkRank = FMath::Min(Level / 5, 3); // I to III

    TArray<FString> PerkNames = {
        "Rampage", "Killstreak", "Headhunter", "Tactical",
        "Berserker", "Sharpshooter", "Hunter", "Survivor"
    };
    int32 PerkIndex = (Level / 5 - 1) % PerkNames.Num();
    Perk.PerkName = FString::Printf(TEXT("%s II+%d"),
        *PerkNames[PerkIndex], Perk.PerkRank);
    Perk.Description = FString::Printf(
        TEXT("+%d%% Damage | +%d%% Fire Rate per stack"),
        Perk.PerkRank * 5, Perk.PerkRank * 3);

    FLinearColor PerkColors[] = {
        FLinearColor(0.3f, 0.8f, 0.3f),  // Green
        FLinearColor(0.2f, 0.6f, 0.9f),  // Blue
        FLinearColor(0.8f, 0.4f, 0.9f)   // Purple
    };
    Perk.PerkColor = PerkColors[FMath::Min(Perk.PerkRank - 1, 2)];

    State.UnlockedPerks.Add(Perk);
}

bool UWeaponProgressionComponent::CanUpgradeRarity() const {
    for (const auto& Path : RarityUpgradePaths) {
        if (Path.FromRarity == State.CurrentRarity) {
            return State.CurrentXP >= Path.UpgradeXP;
        }
    }
    return false;
}

bool UWeaponProgressionComponent::TryRarityUpgrade() {
    if (!CanUpgradeRarity()) return false;

    for (auto& Path : RarityUpgradePaths) {
        if (Path.FromRarity == State.CurrentRarity) {
            State.CurrentXP -= Path.UpgradeXP;
            State.CurrentRarity = Path.ToRarity;

            UE_LOG(LogTemp, Log, TEXT("RarityUpgrade: %s -> %s (XP Cost: %d)"),
                *UEnum::GetValueAsName(Path.FromRarity).ToString(),
                *UEnum::GetValueAsName(Path.ToRarity).ToString(),
                Path.UpgradeXP);

            OnRarityUpgrade.Broadcast(Path.FromRarity, Path.ToRarity, Path.UpgradeXP);
            return true;
        }
    }
    return false;
}

void UWeaponProgressionComponent::ResetProgression() {
    State = FWeaponProgressionState();
    UE_LOG(LogTemp, Log, TEXT("Weapon progression reset"));
}
