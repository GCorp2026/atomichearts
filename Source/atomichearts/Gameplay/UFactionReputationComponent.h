#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Game/AtomichartsTypes.h"
#include "UFactionReputationComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ATOMICHEARTS_API UFactionReputationComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UFactionReputationComponent();

    // Faction Reputation (0-100 per faction)
    UFUNCTION(BlueprintPure, Category = "Faction")
    int32 GetReputation(EFaction Faction) const;

    UFUNCTION(BlueprintCallable, Category = "Faction")
    void AddReputation(EFaction Faction, int32 Amount);

    UFUNCTION(BlueprintPure, Category = "Faction")
    float GetReputationNormalized(EFaction Faction) const;

    UFUNCTION(BlueprintPure, Category = "Faction")
    EFactionRank GetRank(EFaction Faction) const;

protected:
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

    UFUNCTION()
    void OnRep_Reputations();

    UPROPERTY(Replicated, BlueprintReadOnly, Category = "Faction")
    TMap<EFaction, int32> Reputations;

    void InitializeReputations();
};
