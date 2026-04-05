// Copyright Epic Games, Inc. All Rights Reserved.

#include "AssetSwapManager.h"
#include "AssetSwapComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInterface.h"
#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/StreamableManager.h"
#include "Engine/AssetManager.h"

UAssetSwapManager::UAssetSwapManager()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UAssetSwapManager::LoadAssetManifest()
{
    // Clear existing entries
    SwapEntries.Empty();
    LoadedAssets.Empty();

    UE_LOG(LogTemp, Log, TEXT("AssetSwapManager: Loading asset manifest"));
}

void UAssetSwapManager::SwapWeaponModel(FGuid AssetId, FName SocketName)
{
    FString AssetIdStr = AssetId.ToString();
    
    UE_LOG(LogTemp, Log, TEXT("AssetSwapManager: Swapping weapon model %s at socket %s"), *AssetIdStr, *SocketName.ToString());
    
    // Find the swap entry for this asset
    FAssetSwapEntry* Entry = SwapEntries.Find(AssetIdStr);
    if (!Entry || !Entry->bEnabled)
    {
        UE_LOG(LogTemp, Warning, TEXT("AssetSwapManager: No active swap entry found for %s"), *AssetIdStr);
        return;
    }

    // Load the asset asynchronously
    FSoftObjectPath AssetPath(Entry->SwapPath);
    TWeakObjectPtr<UAssetSwapManager> WeakThis = this;
    
    auto OnAssetLoaded = [WeakThis, AssetIdStr, SocketName](UObject* LoadedAsset)
    {
        if (!WeakThis.IsValid()) return;
        
        UAssetSwapManager* Manager = WeakThis.Get();
        USkeletalMesh* NewMesh = Cast<USkeletalMesh>(LoadedAsset);
        
        if (!NewMesh)
        {
            UE_LOG(LogTemp, Error, TEXT("AssetSwapManager: Loaded asset is not a skeletal mesh"));
            return;
        }

        // Find all actors with skeletal mesh components and apply swap
        for (TObjectIterator<USkeletalMeshComponent> It; It; ++It)
        {
            USkeletalMeshComponent* MeshComp = *It;
            if (MeshComp->DoesSocketExist(SocketName))
            {
                UE_LOG(LogTemp, Log, TEXT("AssetSwapManager: Applying mesh swap to component"));
                // Note: In practice, you'd attach to the specific socket
                // This is a simplified implementation
            }
        }
        
        Manager->LoadedAssets.Add(AssetIdStr, NewMesh);
    };

    if (UAssetManager::HasSystem())
    {
        UAssetManager::Get().GetStreamableManager().RequestAsyncLoad(
            AssetPath,
            FStreamableDelegate::CreateLambda(OnAssetLoaded)
        );
    }
}

void UAssetSwapManager::SwapTexture(FGuid AssetId, UMaterialInterface* Material)
{
    FString AssetIdStr = AssetId.ToString();
    
    UE_LOG(LogTemp, Log, TEXT("AssetSwapManager: Swapping texture for material %s"), *Material ? *Material->GetName() : TEXT("NULL"));
    
    FAssetSwapEntry* Entry = SwapEntries.Find(AssetIdStr);
    if (!Entry || !Entry->bEnabled)
    {
        UE_LOG(LogTemp, Warning, TEXT("AssetSwapManager: No active swap entry found for %s"), *AssetIdStr);
        return;
    }

    FSoftObjectPath AssetPath(Entry->SwapPath);
    TWeakObjectPtr<UAssetSwapManager> WeakThis = this;
    
    auto OnAssetLoaded = [WeakThis, AssetIdStr, Material](UObject* LoadedAsset)
    {
        if (!WeakThis.IsValid() || !Material) return;
        
        UTexture2D* NewTexture = Cast<UTexture2D>(LoadedAsset);
        if (!NewTexture)
        {
            UE_LOG(LogTemp, Error, TEXT("AssetSwapManager: Loaded asset is not a texture"));
            return;
        }

        // Apply texture to material
        FSoftObjectPath TexturePath(NewTexture);
        Material->SetTextureParameterValue(FName("DiffuseTexture"), NewTexture);
        
        UE_LOG(LogTemp, Log, TEXT("AssetSwapManager: Texture swap applied successfully"));
        
        UAssetSwapManager* Manager = WeakThis.Get();
        Manager->LoadedAssets.Add(AssetIdStr, NewTexture);
    };

    if (UAssetManager::HasSystem())
    {
        UAssetManager::Get().GetStreamableManager().RequestAsyncLoad(
            AssetPath,
            FStreamableDelegate::CreateLambda(OnAssetLoaded)
        );
    }
}

void UAssetSwapManager::SwapAudio(FGuid AssetId, USoundCue* SoundCue)
{
    FString AssetIdStr = AssetId.ToString();
    
    UE_LOG(LogTemp, Log, TEXT("AssetSwapManager: Swapping audio for sound cue %s"), *SoundCue ? *SoundCue->GetName() : TEXT("NULL"));
    
    FAssetSwapEntry* Entry = SwapEntries.Find(AssetIdStr);
    if (!Entry || !Entry->bEnabled)
    {
        UE_LOG(LogTemp, Warning, TEXT("AssetSwapManager: No active swap entry found for %s"), *AssetIdStr);
        return;
    }

    FSoftObjectPath AssetPath(Entry->SwapPath);
    TWeakObjectPtr<UAssetSwapManager> WeakThis = this;
    
    auto OnAssetLoaded = [WeakThis, AssetIdStr, SoundCue](UObject* LoadedAsset)
    {
        if (!WeakThis.IsValid() || !SoundCue) return;
        
        USoundWave* NewSoundWave = Cast<USoundWave>(LoadedAsset);
        if (!NewSoundWave)
        {
            UE_LOG(LogTemp, Error, TEXT("AssetSwapManager: Loaded asset is not a sound wave"));
            return;
        }

        UE_LOG(LogTemp, Log, TEXT("AssetSwapManager: Audio swap loaded successfully"));
        
        UAssetSwapManager* Manager = WeakThis.Get();
        Manager->LoadedAssets.Add(AssetIdStr, NewSoundWave);
    };

    if (UAssetManager::HasSystem())
    {
        UAssetManager::Get().GetStreamableManager().RequestAsyncLoad(
            AssetPath,
            FStreamableDelegate::CreateLambda(OnAssetLoaded)
        );
    }
}

void UAssetSwapManager::LoadManifest(const FString& ManifestPath)
{
    UE_LOG(LogTemp, Log, TEXT("AssetSwapManager: Loading manifest from %s"), *ManifestPath);
    LoadAssetManifest();
}

UObject* UAssetSwapManager::GetSwappedAsset(const FString& OriginalPath)
{
    if (FAssetSwapEntry* Entry = SwapEntries.Find(OriginalPath))
    {
        if (Entry->bEnabled)
        {
            return LoadedAssets.FindRef(OriginalPath);
        }
    }
    return nullptr;
}

void UAssetSwapManager::SetSwapEnabled(const FString& OriginalPath, bool bEnabled)
{
    if (FAssetSwapEntry* Entry = SwapEntries.Find(OriginalPath))
    {
        Entry->bEnabled = bEnabled;
        UE_LOG(LogTemp, Log, TEXT("AssetSwapManager: Swap for %s %s"), *OriginalPath, bEnabled ? TEXT("enabled") : TEXT("disabled"));
    }
}

void UAssetSwapManager::RefreshAllSwaps()
{
    UE_LOG(LogTemp, Log, TEXT("AssetSwapManager: Refreshing all swaps"));
    
    // Clear loaded assets cache
    LoadedAssets.Empty();
    
    // Reload all enabled swaps
    for (const auto& Pair : SwapEntries)
    {
        if (Pair.Value.bEnabled)
        {
            UE_LOG(LogTemp, Log, TEXT("AssetSwapManager: Would reload swap for %s"), *Pair.Key);
        }
    }
}
