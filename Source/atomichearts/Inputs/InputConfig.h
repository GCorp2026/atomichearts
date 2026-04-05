// Copyright (c) 2026 Atomic Hearts Team. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "InputConfig.generated.h"

class UInputAction;

USTRUCT(BlueprintType)
struct FAtomichartsInputAction
{
    GENERATED_BODY()

public:
    UPROPERTY(EditDefaultsOnly)
    const UInputAction* InputAction = nullptr;

    UPROPERTY(EditDefaultsOnly, Meta = (Categories = "InputTag"))
    FGameplayTag InputTag;
};

/**
 * UAtomichartsInputConfig - Data asset for cyberpunk input mappings
 * Contains all input actions for movement abilities: Sprint, Slide, DoubleJump, Dodge
 */
UCLASS()
class ATOMICHEARTS_API UAtomichartsInputConfig : public UDataAsset
{
    GENERATED_BODY()

public:
    const UInputAction* FindNativeInputActionForTag(const FGameplayTag& InputTag) const;

public:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Meta = (TitleProperty = "InputAction"))
    TArray<FAtomichartsInputAction> NativeInputActions;
};
