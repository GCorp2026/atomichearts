#include "Components/FactionReputationComponent.h"
#include "Game/AtomichartsTypes.h"

UFactionReputationComponent::UFactionReputationComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
    SetIsReplicated(true);
}

void UFactionReputationComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(UFactionReputationComponent, Reputations);
}

void UFactionReputationComponent::InitializeReputations()
{
    Reputations.Empty();
    Reputations.Add(EFaction::Vanguard, 0);
    Reputations.Add(EFaction::Renegades, 0);
    Reputations.Add(EFaction::Collectors, 0);
    Reputations.Add(EFaction::FirstLight, 0);
}

int32 UFactionReputationComponent::GetReputation(EFaction Faction) const
{
    if (const int32* Value = Reputations.Find(Faction))
    {
        return FMath::Clamp(*Value, 0, 100);
    }
    return 0;
}

void UFactionReputationComponent::AddReputation(EFaction Faction, int32 Amount)
{
    if (!HasAuthority())
        return;

    if (!Reputations.Contains(Faction))
    {
        Reputations.Add(Faction, 0);
    }

    int32 NewValue = Reputations[Faction] + Amount;
    Reputations[Faction] = FMath::Clamp(NewValue, 0, 100);
}

float UFactionReputationComponent::GetReputationNormalized(EFaction Faction) const
{
    return GetReputation(Faction) / 100.f;
}

EFactionRank UFactionReputationComponent::GetRank(EFaction Faction) const
{
    const int32 Rep = GetReputation(Faction);

    if (Rep >= 90) return EFactionRank::Legendary;
    if (Rep >= 75) return EFactionRank::Master;
    if (Rep >= 50) return EFactionRank::Veteran;
    if (Rep >= 25) return EFactionRank::Initiate;
    return EFactionRank::Neutral;
}

void UFactionReputationComponent::OnRep_Reputations()
{
    // Client-side handling if needed
}
