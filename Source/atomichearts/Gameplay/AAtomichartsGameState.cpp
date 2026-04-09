#include "Game/AAtomichartsGameState.h"
#include "Game/AtomichartsTypes.h"
#include "Marketplace/UMarketplaceManager.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

AAtomichartsGameState::AAtomichartsGameState()
{
    MarketplaceManager = CreateDefaultSubobject<UMarketplaceManager>(TEXT("MarketplaceManager"));
}

void AAtomichartsGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(AAtomichartsGameState, MatchState);
    DOREPLIFETIME(AAtomichartsGameState, RedTeamScore);
    DOREPLIFETIME(AAtomichartsGameState, BlueTeamScore);
    DOREPLIFETIME(AAtomichartsGameState, MatchTimeRemaining);
    DOREPLIFETIME(AAtomichartsGameState, HouseBalance);
}

void AAtomichartsGameState::StartMatch()
{
    MatchState = EMatchState::InProgress;
    MatchTimeRemaining = MatchDuration;

    GetWorld()->GetTimerManager().SetTimer(
        MatchTimerHandle,
        this,
        &AAtomichartsGameState::MatchTimerTick,
        1.f,
        true
    );
}

void AAtomichartsGameState::MatchTimerTick()
{
    if (MatchTimeRemaining <= 0)
    {
        EndMatch();
    }
    else
    {
        MatchTimeRemaining--;
    }
}

void AAtomichartsGameState::EndMatch()
{
    MatchState = EMatchState::Finished;
    GetWorld()->GetTimerManager().ClearTimer(MatchTimerHandle);

    for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
    {
        if (AAtomichartsPlayerController* PC = Cast<AAtomichartsPlayerController>(*It))
        {
            PC->ClientMatchEnded(RedTeamScore > BlueTeamScore ? 0 : 1);
        }
    }
}

void AAtomichartsGameState::AddTeamScore(int32 Team, int32 Points)
{
    if (Team == 0)
    {
        RedTeamScore += Points;
    }
    else
    {
        BlueTeamScore += Points;
    }
}

FText AAtomichartsGameState::GetMatchTimeText() const
{
    const int32 Minutes = static_cast<int32>(MatchTimeRemaining) / 60;
    const int32 Seconds = static_cast<int32>(MatchTimeRemaining) % 60;
    return FText::FromString(FString::Printf(TEXT("%02d:%02d"), Minutes, Seconds));
}

int32 AAtomichartsGameState::GetLeadingTeam() const
{
    if (RedTeamScore > BlueTeamScore) return 0;
    if (BlueTeamScore > RedTeamScore) return 1;
    return -1;
}

void AAtomichartsGameState::OnRep_MatchState()
{
    // Client-side handling if needed
}

void AAtomichartsGameState::BeginPlay()
{
    Super::BeginPlay();
    BindMarketplaceEvents();
}

void AAtomichartsGameState::BindMarketplaceEvents()
{
    if (MarketplaceManager)
    {
        MarketplaceManager->OnItemSold.AddDynamic(this, &AAtomichartsGameState::OnMarketplaceItemSold);
        UE_LOG(LogTemp, Log, TEXT("GameState: Bound to Marketplace OnItemSold"));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("GameState: MarketplaceManager is null, cannot bind events"));
    }
}

void AAtomichartsGameState::OnMarketplaceItemSold(int64 SellerID, int64 BuyerID, const FString& ItemID, int32 Price, int32 Payout, int32 Commission)
{
    // Only server should process commission
    if (!HasAuthority()) return;
    // Add commission to house balance
    AddHouseBalance(Commission);
    UE_LOG(LogTemp, Log, TEXT("House account: +%d commission from sale of %s (Price=%d, Payout=%d). New balance: %d"), Commission, *ItemID, Price, Payout, HouseBalance);
}

void AAtomichartsGameState::AddHouseBalance(int32 Amount)
{
    if (!HasAuthority()) return;
    if (Amount <= 0) return;
    HouseBalance += Amount;
    UE_LOG(LogTemp, Log, TEXT("House account: +%d added. New balance: %d"), Amount, HouseBalance);
    // Could broadcast a delegate here if needed
}

bool AAtomichartsGameState::WithdrawHouseBalance(int32 Amount)
{
    if (!HasAuthority()) return false;
    if (Amount <= 0 || Amount > HouseBalance) return false;
    HouseBalance -= Amount;
    UE_LOG(LogTemp, Log, TEXT("House account: -%d withdrawn. New balance: %d"), Amount, HouseBalance);
    return true;
}
