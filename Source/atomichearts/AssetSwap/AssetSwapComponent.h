#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AssetSwapComponent.generated.h"

UCLASS(ClassGroup=(AssetSwap), meta=(BlueprintSpawnableComponent))
class ATOMICHEARTS_API UAssetSwapComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UAssetSwapComponent();

    UFUNCTION(BlueprintCallable)
    void InitializeSwapManager();

    UFUNCTION(BlueprintCallable)
    void ApplySwapToActor(AActor* TargetActor);

protected:
    UPROPERTY()
    class UAssetSwapManager* SwapManager;
};
