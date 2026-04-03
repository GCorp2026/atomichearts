# ASSET PIPELINE INTEGRATION

## Current atomicsoul-assets Architecture

**Frontend:** React + Vite + Tailwind + lucide-react
**Backend:** Node.js server with routes:
- POST /api/auth/login
- POST /api/auth/register  
- GET /api/manifest
- GET /api/download/:id
- POST /api/upload
- POST /api/generate (Nano Banana AI)
- PUT /api/assets/:id (update game_path, swap_enabled)

**Storage:** Local filesystem at /uploads or similar

## 1. UE5 Side: AssetSwapManager Updates

```cpp
UCLASS()
class UAtomichartsAssetAPI : public UObject {
    GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere, Category="Config")
    FString APIBaseURL = "http://localhost:3001";
    
    UPROPERTY(EditAnywhere, Category="Config") 
    FString APIKey; // JWT token
    
    UFUNCTION(BlueprintCallable)
    TArray<FManifestAsset> FetchManifest();
    
    UFUNCTION(BlueprintCallable)
    bool DownloadAsset(int32 AssetID, FString SavePath);
    
    UFUNCTION(BlueprintCallable)
    void SyncAllAssets();
};
```

## 2. AssetSwapManager Integration

```cpp
void UAssetSwapManager::LoadManifestFromAPI() {
    UAtomichartsAssetAPI* API = NewObject<UAtomichartsAssetAPI>();
    TArray<FManifestAsset> Assets = API->FetchManifest();
    
    for (auto Asset : Assets) {
        if (Asset.swap_enabled) {
            FAssetSwapEntry Entry;
            Entry.OriginalPath = Asset.GamePath;
            Entry.SwapPath = Asset.Url;
            Entry.bEnabled = true;
            Entry.bIsAI = Asset.ai_generated;
            SwapEntries.Add(Asset.Name, Entry);
        }
    }
}
```

## 3. New UI: UE5 Export Dropdown

In atomicsoul-assets, add to Assets.tsx:

```tsx
<div className="mb-4">
  <label className="block text-white mb-2">Export to Engine</label>
  <select 
    className="bg-gray-800 text-white p-2 rounded"
    onChange={(e) => handleEngineExport(e.target.value)}
  >
    <option value="">Select Game...</option>
    <option value="atomichearts">Atomic Hearts (UE5)</option>
    <option value="custom">Custom Path...</option>
  </select>
</div>
```

## 4. GamePath Convention for atomichearts

```
Weapons/Primary/Axiom_AR7.uasset
Weapons/Secondary/Neon_HC9.uasset
Armor/Helmet/Chrome_Security_Hood.uasset
Characters/Skins/Axiom_Security_Variant.uasset
Environment/Props/Neon_Sign_Pack.uasset
Audio/Weapons/Gun_Fire.uasset
Audio/UI/Menu_Click.uasset
```

## 5. Files to Create

### On atomichearts side:
```
Source/atomichearts/AssetPipeline/
  UAtomichartsAssetAPI.h/.cpp
  UAssetSyncManager.h/.cpp
  FManifestAsset.h (struct)
```

### On atomicsoul-assets side:
```
src/components/UE5ExportDropdown.tsx
src/pages/Assets.tsx (modify)
server/routes/export.js (new)
```

## 6. Nano Banana AI Integration

Already exists in atomicsoul-assets Generate.tsx:
- Prompts sent to Nano Banana API
- Generated assets stored locally
- Can export to UE5 via manifest

### Workflow
1. Artist opens atomicsoul-assets
2. Uses "Generate" page with Nano Banana
3. Generated asset saved to library
4. Sets "Use in Game" toggle
5. Sets GamePath to match atomichearts structure
6. atomichearts syncs via AssetSwapManager

## 7. Hot Reload System

```cpp
void UAtomichartsGameInstance::OnAssetManifestUpdated() {
    AssetSwapManager->LoadManifestFromAPI();
    for (auto PC : PlayerControllerList) {
        PC->ClientRefreshInventory();
    }
}
```
