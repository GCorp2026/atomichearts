#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "AssetSwapManager.generated.h"

USTRUCT(BlueprintType)
struct FAssetSwapEntry
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString OriginalPath;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString SwapPath;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bEnabled = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bIsAI = false;
};

UCLASS(Blueprintable)
class ATOMICHEARTS_API UAssetSwapManager : public UObject
{
    GENERATED_BODY()

public:
    UAssetSwapManager();

    UFUNCTION(BlueprintCallable)
    void LoadManifest(const FString& ManifestPath);

    UFUNCTION(BlueprintCallable)
    UObject* GetSwappedAsset(const FString& OriginalPath);

    UFUNCTION(BlueprintCallable)
    void SetSwapEnabled(const FString& OriginalPath, bool bEnabled);

    UFUNCTION(BlueprintCallable)
    void RefreshAllSwaps();

protected:
    UPROPERTY()
    TMap<FString, FAssetSwapEntry> SwapEntries;

    UPROPERTY()
    TMap<FString, UObject*> LoadedAssets;
};
