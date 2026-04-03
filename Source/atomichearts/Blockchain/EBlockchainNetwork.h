// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EBlockchainNetwork.generated.h"

/**
 * Supported blockchain networks for item registration
 */
UENUM(BlueprintType)
enum class EBlockchainNetwork : uint8
{
    Local    UMETA(DisplayName = "Local (Simulated)"),
    Polygon  UMETA(DisplayName = "Polygon Testnet"),
    Ethereum UMETA(DisplayName = "Ethereum Testnet")
};
