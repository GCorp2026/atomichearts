// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "AssetSwapManager.generated.h"

class USoundCue;
class UMaterialInterface;

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

    /** Load the asset manifest from the server */
    UFUNCTION(BlueprintCallable)
    void LoadAssetManifest();

    /** Swap a weapon model at the specified socket */
    UFUNCTION(BlueprintCallable)
    void SwapWeaponModel(FGuid AssetId, FName SocketName);

    /** Swap a texture on a material */
    UFUNCTION(BlueprintCallable)
    void SwapTexture(FGuid AssetId, UMaterialInterface* Material);

    /** Swap audio on a sound cue */
    UFUNCTION(BlueprintCallable)
    void SwapAudio(FGuid AssetId, USoundCue* SoundCue);

    /** Legacy manifest loading */
    UFUNCTION(BlueprintCallable)
    void LoadManifest(const FString& ManifestPath);

    /** Get a previously swapped asset */
    UFUNCTION(BlueprintCallable)
    UObject* GetSwappedAsset(const FString& OriginalPath);

    /** Enable or disable a specific swap */
    UFUNCTION(BlueprintCallable)
    void SetSwapEnabled(const FString& OriginalPath, bool bEnabled);

    /** Refresh all active swaps */
    UFUNCTION(BlueprintCallable)
    void RefreshAllSwaps();

protected:
    UPROPERTY()
    TMap<FString, FAssetSwapEntry> SwapEntries;

    UPROPERTY()
    TMap<FString, UObject*> LoadedAssets;
};
