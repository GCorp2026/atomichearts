#include "Components/ProgressionComponent.h"

UProgressionComponent::UProgressionComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
    SetIsReplicated(true);
}

void UProgressionComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(UProgressionComponent, XP);
    DOREPLIFETIME(UProgressionComponent, Level);
    DOREPLIFETIME(UProgressionComponent, LightLevel);
}

void UProgressionComponent::AddXP(int32 Amount)
{
    if (!HasAuthority())
        return;

    XP += Amount;

    // Level up check
    while (XP >= GetXPToNextLevel())
    {
        XP -= GetXPToNextLevel();
        Level++;
        LightLevel = CalculateLightLevelFromLevel();
    }
}

int32 UProgressionComponent::GetXPToNextLevel() const
{
    return XPPerLevel * Level;
}

int32 UProgressionComponent::CalculateLightLevelFromLevel() const
{
    // Linear scale from 1-2000 based on level
    return FMath::Clamp(Level, 1, 2000);
}

int32 UProgressionComponent::GetLightLevel() const
{
    return FMath::Clamp(LightLevel, 1, 2000);
}

void UProgressionComponent::SetLightLevel(int32 NewLevel)
{
    if (!HasAuthority())
        return;

    LightLevel = FMath::Clamp(NewLevel, 1, 2000);
}

float UProgressionComponent::GetXPProgress() const
{
    const int32 XPForNextLevel = GetXPToNextLevel();
    if (XPForNextLevel <= 0)
        return 0.f;

    return static_cast<float>(XP) / static_cast<float>(XPForNextLevel);
}
