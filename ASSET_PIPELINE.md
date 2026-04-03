# Asset Pipeline Integration Plan

## 1. Current atomicsoul-assets Architecture

### Frontend
- **Stack**: React + Vite + Tailwind CSS + lucide-react + react-dropzone
- **Pages**:
  - `Assets.tsx` — Asset library with grid, upload zone, filtering, search, tags, version history, comments
  - `Generate.tsx` — AI generation via Nano Banana API
  - `UE5Export.tsx` — **Already exists** — manifest viewer and export UI
  - `Auth.tsx` — Login/signup form

### Backend
- **Stack**: Express.js + PostgreSQL (on artem-1: `100.112.245.6`)
- **Auth**: JWT via `bcryptjs`; token in `Authorization: Bearer <token>` header
- **Storage**: 
  - Uploads: `/var/www/atomicsoul-assets/uploads/`
  - Generated: `/var/www/atomicsoul-assets/generated/`

### Key API Routes
| Method | Path | Description |
|--------|------|-------------|
| POST | `/api/auth/login` | Login → `{token, user}` |
| POST | `/api/auth/register` | Register → `{token, user}` |
| GET | `/api/assets` | List user's assets |
| POST | `/api/assets/upload` | Upload file (multer, 50MB max) |
| PUT | `/api/assets/:id/game-path` | Set UE5 game path |
| DELETE | `/api/assets/:id` | Delete asset |
| POST | `/api/generate` | AI generate via Nano Banana |
| GET | `/api/manifest` | **Get UE5 manifest** (swap-enabled assets) |
| GET | `/api/export` | Export all assets as JSON |
| GET | `/api/download/:id` | Download single asset file |
| POST | `/api/assets/:id/tags` | Add tag to asset |
| GET | `/api/tags` | List all tags |

### Current Manifest Format (`/api/manifest`)
```json
{
  "version": "1.0",
  "asset_count": 2,
  "assets": [
    {
      "Name": "filename.png",
      "Type": "texture",
      "GamePath": "/Game/Assets/Textures/filename.png",
      "Url": "/uploads/xxx.png",
      "AIGenerated": true
    }
  ]
}
```

## 2. How to Add "Export to UE5" Dropdown

### Current Upload Flow (Assets.tsx)
1. User drops files into the `useDropzone` area
2. `onDrop` iterates `acceptedFiles`, POSTs each to `/api/assets/upload` with `FormData`
3. Server saves to `/var/www/atomicsoul-assets/uploads/`, creates DB record
4. Asset appears in grid with "Use in Game" toggle (sets `swap_enabled=true`)

### Where to Add UE5 Export Dropdown
Add a **dropdown button** in the **Asset Card** action bar (next to "Use in Game" button):
```tsx
{/* Replace or extend the "Use in Game" button area */}
<div className="flex gap-2 mt-3">
  <UE5ExportDropdown asset={asset} token={token} />
  <button className={`flex-1 px-3 py-2 rounded text-sm...`}>
    {asset.swap_enabled ? "Active" : "Use in Game"}
  </button>
</div>
```

### New UI Component: `UE5ExportDropdown`
- Small dropdown (Export to UE5 ▼)
- Options: "Copy Game Path", "Copy Manifest Entry", "Download Asset"
- Fetches `/api/manifest` entry for this asset
- Copies `GamePath` to clipboard for UE5 reference

## 3. Manifest.json Format for UE5

### Current Structure
The manifest already exists at `/api/manifest` — it filters assets with `swap_enabled=true`.

### Fields UE5 AssetSwapManager Needs
```json
{
  "Name": "filename.png",
  "Type": "texture | model | audio",
  "GamePath": "/Game/Assets/Textures/filename.png",
  "Url": "/uploads/xxx.png",
  "AIGenerated": true,
  "FileSize": 1048576,
  "Checksum": "sha256:abc123...",
  "SwapEnabled": true
}
```

### AssetSwapManager Reading Flow
1. UE5 calls `/api/manifest` with auth token
2. Server returns JSON manifest
3. AssetSwapManager parses `assets[]`, downloads each via `/api/download/:id`
4. Places files at `GamePath` location in UE5 Content Browser

## 4. Integration Steps

### Step 1: Modify atomicsoul-assets — Add UE5 Export Dropdown
- Create `src/components/UE5ExportDropdown.tsx`
- Add to asset card in `Assets.tsx` (import and render)
- Style: small gray dropdown button "UE5 ▼"

### Step 2: Update Server API — Enhance Manifest
Modify `/api/manifest` endpoint to add `FileSize` and `Checksum` fields:
```typescript
// Add to manifest asset object:
FileSize: r.file_size,
Checksum: await computeChecksum(path.join(UPLOAD_DIR, path.basename(r.path)))
```

### Step 3: Connect AssetSwapManager to API
In UE5 C++:
```cpp
// In AssetSwapManager
void UAssetSwapManager::FetchManifest(const FString& AuthToken)
{
    TArray<TPair<FString, FString>> Headers;
    Headers.Add(TPair<FString, FString>("Authorization", "Bearer " + AuthToken));
    
    Http->Get(TEXT("http://localhost:3001/api/manifest"), Headers,
        [&](TSharedPtr<IHttpResponse> Response) {
            // Parse JSON, download assets
        });
}
```

### Step 4: Test Asset Swap Flow
1. Upload asset in atomicsoul-assets → enable "Use in Game"
2. UE5 calls `/api/manifest` → gets asset list
3. UE5 downloads each asset via `/api/download/:id`
4. UE5 places file at `GamePath` → swap active

## 5. Code to Write

### New Files in atomicsoul-assets

| File | Purpose |
|------|---------|
| `src/components/UE5ExportDropdown.tsx` | Dropdown per asset card for UE5 export actions |
| `src/components/UE5BulkExport.tsx` | Bulk export panel for selected assets |
| `server/manifest-enhancer.ts` | Add FileSize/Checksum to manifest endpoint |

### Modifications to Existing Files

| File | Change |
|------|--------|
| `src/pages/Assets.tsx` | Import and render `UE5ExportDropdown` in asset card |
| `src/pages/Assets.tsx` | Add checkbox selection for bulk UE5 export |
| `server/index.ts` | Modify `/api/manifest` to include `file_size` and compute checksum |
| `server/index.ts` | Add optional `?ids=1,2,3` filter to `/api/manifest` for bulk |
| `vite.config.ts` | Add `VITE_API_URL` proxy if needed for UE5 |

### C++ Changes to AssetSwapManager

**`AssetSwapManager.h`**
```cpp
void FetchManifest(const FString& AuthToken);
void DownloadAsset(int32 AssetId, const FString& SavePath);
void SwapAsset(const FManifestEntry& Entry);
```

**`AssetSwapManager.cpp`**
- `FetchManifest()` — GET `/api/manifest`, parse JSON response
- `DownloadAsset()` — GET `/api/download/{id}` with auth header, save to disk
- `SwapAsset()` — Move downloaded file to `GamePath`, notify UE5 asset registry

---

**Key Finding**: `UE5Export.tsx` already exists in atomicsoul-assets. It provides a full-page manifest viewer with type filters and JSON export. The integration path is: Assets page → enable swap → UE5Export page → download/export → UE5 AssetSwapManager consumes manifest + downloads files.
