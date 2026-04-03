// Copyright Epic Games, Inc. All Rights Reserved.

#include "Blockchain/UBlockchainItemRegistry.h"
#include "Kismet/KismetStringLibrary.h"

#define FNV1a_PRIME 0x01000193u
#define FNV1a_OFFSET 0x811c9dc5u

FString UBlockchainItemRegistry::GenerateTokenID(int32 Seed, FString ItemType, FString Slot)
{
    // Combine inputs into single string for hashing
    FString Combined = FString::Printf(TEXT("%d_%s_%s_%lld"), 
        Seed, *ItemType, *Slot, FDateTime::UtcNow().ToUnixTimestamp());
    
    uint32 Hash = FNV1a_OFFSET;
    
    // Process string as bytes
    for (const TCHAR& Char : Combined)
    {
        Hash ^= static_cast<uint32>(Char);
        Hash *= FNV1a_PRIME;
    }
    
    // Convert to hex string with sha256 prefix for realism
    return FString::Printf(TEXT("sha256_%08x"), Hash);
}

FItemToken UBlockchainItemRegistry::RegisterItem(int32 Seed, FString ItemType, FString Slot,
                                                  FString Name, FString Rarity, int64 OwnerID)
{
    FItemToken Token;
    Token.TokenID = GenerateTokenID(Seed, ItemType, Slot);
    Token.OwnerID = FString::Printf(TEXT("%lld"), OwnerID);
    Token.ItemType = ItemType;
    Token.ItemClass = Slot;
    Token.Seed = Seed;
    Token.Name = Name;
    Token.Rarity = Rarity;
    Token.CreatedAt = FDateTime::UtcNow().ToUnixTimestamp();
    Token.LastTradedAt = Token.CreatedAt;
    Token.LastPrice = 0;

    ItemRegistry.Add(Token.TokenID, Token);
    return Token;
}

bool UBlockchainItemRegistry::TransferItem(FString TokenID, int64 FromOwner, int64 ToOwner, int32 Price)
{
    FItemToken* Token = ItemRegistry.Find(TokenID);
    if (!Token)
    {
        return false;
    }

    // Verify ownership
    FString FromOwnerStr = FString::Printf(TEXT("%lld"), FromOwner);
    if (Token->OwnerID != FromOwnerStr)
    {
        return false;
    }

    // Update token
    Token->OwnerID = FString::Printf(TEXT("%lld"), ToOwner);
    Token->LastTradedAt = FDateTime::UtcNow().ToUnixTimestamp();
    Token->LastPrice = Price;

    return true;
}

FItemToken UBlockchainItemRegistry::GetItem(FString TokenID)
{
    if (FItemToken* Token = ItemRegistry.Find(TokenID))
    {
        return *Token;
    }
    
    return FItemToken{};
}

TArray<FItemToken> UBlockchainItemRegistry::GetOwnerItems(int64 OwnerID)
{
    TArray<FItemToken> OwnerTokens;
    FString OwnerIDStr = FString::Printf(TEXT("%lld"), OwnerID);

    for (const auto& Pair : ItemRegistry)
    {
        if (Pair.Value.OwnerID == OwnerIDStr)
        {
            OwnerTokens.Add(Pair.Value);
        }
    }
    
    return OwnerTokens;
}

int32 UBlockchainItemRegistry::CalculateCommission(int32 SalePrice)
{
    return static_cast<int32>(SalePrice * 0.30f);
}

int32 UBlockchainItemRegistry::CalculateSellerPayout(int32 SalePrice)
{
    return static_cast<int32>(SalePrice * 0.70f);
}

uint32 UBlockchainItemRegistry::FNV1aHash(const FString& Input)
{
    uint32 Hash = FNV1a_OFFSET;
    
    for (const TCHAR& Char : Input)
    {
        Hash ^= static_cast<uint32>(Char);
        Hash *= FNV1a_PRIME;
    }
    
    return Hash;
}
