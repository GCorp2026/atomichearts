#include "Game/AAtomichartsPlayerState.h"
#include "Components/ProgressionComponent.h"
#include "Components/FactionReputationComponent.h"
#include "Currency/UCurrencyComponent.h"
#include "Inventory/InventoryComponent.h"
#include "Game/AAtomichartsGameState.h"

void AAtomichartsPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(AAtomichartsPlayerState, Kills);
    DOREPLIFETIME(AAtomichartsPlayerState, Deaths);
    DOREPLIFETIME(AAtomichartsPlayerState, TeamID);
}

AAtomichartsPlayerState::AAtomichartsPlayerState()
{
    ProgressionComponent = CreateDefaultSubobject<UProgressionComponent>(TEXT("ProgressionComponent"));
    FactionReputationComponent = CreateDefaultSubobject<UFactionReputationComponent>(TEXT("FactionReputationComponent"));
    CurrencyComponent = CreateDefaultSubobject<UCurrencyComponent>(TEXT("CurrencyComponent"));
    InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("InventoryComponent"));
}

void AAtomichartsPlayerState::BeginPlay()
{
    Super::BeginPlay();

    if (HasAuthority())
    {
        KDRatio = Deaths > 0 ? static_cast<float>(Kills) / Deaths : static_cast<float>(Kills);
    }
}

void AAtomichartsPlayerState::AddKill()
{
    Kills++;
    KDRatio = Deaths > 0 ? static_cast<float>(Kills) / Deaths : static_cast<float>(Kills);

    if (ProgressionComponent)
    {
        ProgressionComponent->AddXP(100);
    }
}

void AAtomichartsPlayerState::AddDeath()
{
    Deaths++;
    KDRatio = Deaths > 0 ? static_cast<float>(Kills) / Deaths : static_cast<float>(Kills);
}

int32 AAtomichartsPlayerState::GetLightLevel() const
{
    if (ProgressionComponent)
    {
        return ProgressionComponent->GetLightLevel();
    }
    return 1;
}
