# Landscape Art Pipeline for atomichearts

This document outlines the landscape art pipeline for atomichearts, a cyberpunk-themed third-person shooter. The pipeline leverages the Unreal Engine MCP server for automated terrain creation, material application, foliage painting, and lighting setup.

## Section 1: Terrain Creation (MCP-assisted)

### 1.1 Create Base Landscape
Use the `create_terrain_landscape` tool to create a new ALandscape actor.

**Parameters:**
- `landscape_name`: Unique name for the landscape actor (e.g., "CyberpunkCity_Landscape")
- `sections_per_component`: Number of sections per component (recommended: 1 for 2017×2017, 2 for 4033×4033)
- `section_size`: Size of each section in quads (63, 127, 255). Use 127 for high-detail terrain.
- `sections_xy`: Number of components along X and Y (e.g., 8 for 2017×2017, 16 for 4033×4033)
- `location_x`, `location_y`, `location_z`: World origin coordinates (typically 0,0,0)

**Recommended sizes for atomichearts cyberpunk city:**
- **2017×2017**: Good for smaller districts, dense urban areas. Use `sections_per_component=1`, `section_size=127`, `sections_xy=8`.
- **4033×4033**: Large-scale cityscapes, spanning multiple districts. Use `sections_per_component=2`, `section_size=127`, `sections_xy=16`.

**Example MCP command (via Python):**
```python
result = create_terrain_landscape(
    unreal_connection,
    landscape_name="CyberpunkCity_Landscape",
    sections_per_component=1,
    section_size=127,
    sections_xy=8,
    location_x=0.0,
    location_y=0.0,
    location_z=0.0
)
```

### 1.2 Import Custom Terrain Heightmap
Use `import_terrain_heightmap` to apply custom terrain elevation from a heightmap image.

**Parameters:**
- `landscape_actor_name`: Name of the existing landscape actor
- `heightmap_image_path`: Absolute path to PNG or RAW heightmap file
- `heightmap_scale`: Scaling factor for height values (e.g., 256.0 for moderate relief, 512.0 for dramatic cliffs)

**Heightmap sources:**
- **World Machine** – procedural terrain generation
- **Gaea** – node‑based terrain sculpting
- **Terragen** – photorealistic landscapes
- **Hand‑painted in Photoshop/GIMP** – artistic control

**Example:**
```python
result = import_terrain_heightmap(
    unreal_connection,
    landscape_actor_name="CyberpunkCity_Landscape",
    heightmap_image_path="/path/to/cyberpunk_heightmap.png",
    heightmap_scale=256.0
)
```

## Section 2: Landscape Material (MCP-assisted)

### 2.1 Create Base Material with LayerBlend
Use `create_landscape_material` to create a master landscape material that uses `LayerBlend` nodes for up to 5 layers.

**Parameters:**
- `material_name`: Name of the new material (e.g., "M_CyberpunkTerrain")
- `blend_mode`: `LB_HeightBlend` for height‑based blending, `LB_WeightBlend` for weight painting
- `num_layers`: Number of layers to support (default 5)

**Material layer structure:**
- **Layer 0**: Grass/Vegetation (greenish tones)
- **Layer 1**: Rock/Cliff (gray/black)
- **Layer 2**: Sand/Snow (light gray/white)
- **Layer 3**: Mud/Path (brown)
- **Layer 4**: Asphalt/Road (dark gray)

### 2.2 Add Individual Layers
Use `add_landscape_material_layer` to define each layer’s textures and properties.

**Parameters per layer:**
- `material_path`: Path to the landscape material asset
- `layer_index`: Layer slot (0‑4)
- `diffuse_texture`: Albedo texture path
- `normal_texture`: Normal map path
- `roughness_texture`: Roughness map path (or constant value)
- `tiling`: UV tiling factor (e.g., 10.0 for grass, 2.0 for rock)

**Example for grass layer:**
```python
result = add_landscape_material_layer(
    unreal_connection,
    material_path="/Game/Materials/Landscapes/M_CyberpunkTerrain",
    layer_index=0,
    diffuse_texture="/Game/Textures/Grass/Grass_D",
    normal_texture="/Game/Textures/Grass/Grass_N",
    roughness_texture="/Game/Textures/Grass/Grass_R",
    tiling=10.0
)
```

### 2.3 Configure HeightBlend Parameters
Use `set_landscape_layer_blend_params` to adjust blending behavior for `LB_HeightBlend`.

**Parameters:**
- `material_path`: Path to the landscape material
- `layer_a_index`: First layer index
- `layer_b_index`: Second layer index
- `blend_height`: Height threshold where blending starts (in Unreal units)
- `blend_falloff`: Smoothness of the transition (0.0‑1.0)

**Recommended settings for atomichearts:**
- Grass → Rock: `blend_height=50.0`, `blend_falloff=0.3`
- Rock → Sand: `blend_height=100.0`, `blend_falloff=0.2`
- Sand → Mud: `blend_height=20.0`, `blend_falloff=0.4`

### 2.4 Apply Material to Landscape
Use `apply_landscape_layer` (existing tool) to assign the material to the landscape actor.

**Example:**
```python
result = apply_landscape_layer(
    unreal_connection,
    landscape_actor_name="CyberpunkCity_Landscape",
    material_path="/Game/Materials/Landscapes/M_CyberpunkTerrain",
    layer_name="Grass_Layer"
)
```

Repeat for each layer.

## Section 3: Foliage & Props (MCP-assisted)

### 3.1 Spawn Individual Trees/Props
Use `spawn_foliage_actor` to place single static meshes (trees, rocks, street props) with precise location and rotation.

**Parameters:**
- `mesh_path`: Path to the static mesh asset
- `location_x`, `location_y`, `location_z`: World coordinates
- `rotation_yaw`, `rotation_pitch`, `rotation_roll`: Rotation in degrees
- `scale_x`, `scale_y`, `scale_z`: Uniform or non‑uniform scaling

**Example (cyberpunk tree):**
```python
result = spawn_foliage_actor(
    unreal_connection,
    mesh_path="/Game/Foliage/Trees/Cyberpunk_Tree_01",
    location_x=1200.0,
    location_y=800.0,
    location_z=50.0,
    rotation_yaw=45.0,
    scale_x=1.2,
    scale_y=1.2,
    scale_z=1.2
)
```

### 3.2 Mass Foliage Painting
Use `paint_foliage_layer` to scatter thousands of instances across the landscape using a foliage brush.

**Parameters:**
- `landscape_actor_name`: Name of the landscape to paint on
- `mesh_path`: Path to the static mesh asset
- `paint_density`: Instances per square Unreal unit (e.g., 0.001 for sparse, 0.01 for dense)
- `brush_radius`: Brush size in Unreal units (e.g., 1024.0)
- `paint_strength`: 0.0‑1.0, controls how many instances are added per brush stroke
- `random_scale_min`, `random_scale_max`: Scale variation range
- `random_rotation`: Whether to apply random Yaw rotation

**Example (scatter debris):**
```python
result = paint_foliage_layer(
    unreal_connection,
    landscape_actor_name="CyberpunkCity_Landscape",
    mesh_path="/Game/Foliage/Props/Debris_Pile_01",
    paint_density=0.0005,
    brush_radius=2048.0,
    paint_strength=0.7,
    random_scale_min=0.8,
    random_scale_max=1.5,
    random_rotation=True
)
```

### 3.3 Asset Sources
- **Quixel Megascans (free with Unreal Engine):** High‑quality photoscanned trees, rocks, ground materials.
- **Polyhaven CC0:** Free HDRIs, textures, and 3D models (trees, rocks, urban props).
- **Kenney CC0:** Simple low‑poly assets for prototyping.
- **Epic Marketplace:** Cyberpunk‑specific packs (e.g., “Cyber City”, “Neon Streets”).

## Section 4: Lighting & Atmosphere (MCP-assisted)

### 4.1 Directional Light (Sun/Moon)
Use `create_directional_light` to place a directional light representing the sun or moon.

**Parameters:**
- `light_name`: Actor name (e.g., "Sunlight", "Moonlight")
- `intensity`: Lux value (2‑3 for daytime, 0.1‑0.3 for night)
- `color`: Light color (RGB, 0‑255) – e.g., (255, 240, 220) for warm sun, (180, 200, 255) for cool moon
- `rotation_yaw`, `rotation_pitch`: Sun/Moon position in sky

**Example (daytime sun):**
```python
result = create_directional_light(
    unreal_connection,
    light_name="Sunlight",
    intensity=2.5,
    color_r=255,
    color_g=240,
    color_b=220,
    rotation_yaw=0.0,
    rotation_pitch=45.0
)
```

### 4.2 Sky Atmosphere
Use `setup_sky_atmosphere` to enable volumetric sky scattering, realistic sunrise/sunset, and aerial perspective.

**Parameters:**
- `sun_light_name`: Name of the directional light acting as the sun
- `rayleigh_scattering_scale`: Intensity of blue scattering (default 0.033)
- `mie_scattering_scale`: Intensity of haze around sun (default 0.005)
- `ground_albedo`: Color of the ground reflecting onto the sky (RGB, 0‑1)

**Example:**
```python
result = setup_sky_atmosphere(
    unreal_connection,
    sun_light_name="Sunlight",
    rayleigh_scattering_scale=0.04,
    mie_scattering_scale=0.008,
    ground_albedo_r=0.3,
    ground_albedo_g=0.2,
    ground_albedo_b=0.1
)
```

### 4.3 Exponential Height Fog
Use `setup_height_fog` to add atmospheric depth and distance fog.

**Parameters:**
- `fog_density`: Density at ground level (0.0‑0.1)
- `fog_height_falloff`: How quickly fog thins with altitude (0.0001‑0.01)
- `fog_inscattering_color`: Color of the fog (RGB, 0‑255)
- `fog_max_opacity`: Maximum opacity (0.0‑1.0)

**Example (cyberpunk haze):**
```python
result = setup_height_fog(
    unreal_connection,
    fog_density=0.02,
    fog_height_falloff=0.001,
    fog_inscattering_color_r=80,
    fog_inscattering_color_g=60,
    fog_inscattering_color_b=120,
    fog_max_opacity=0.7
)
```

## Section 5: Cyberpunk-Specific Tips

### 5.1 Darker Atmospheric Fog
Cyberpunk environments benefit from thicker, colored fog that adds mystery and depth.

**Recommendations:**
- Use purple/blue tints (`RGB 70, 50, 120`) for night scenes.
- Increase fog density (0.03‑0.05) to hide distant LOD pop‑in.
- Lower `fog_height_falloff` (0.0005) to keep fog near the ground.

### 5.2 Neon‑Ready Lighting Setup
- Add multiple **Point Lights** and **Spot Lights** with emissive materials for neon signs.
- Use **Light Functions** with scrolling noise textures to simulate flickering neon.
- Enable **Light Shafts** (god rays) for dramatic volumetric effects.
- Set **Light Mobility** to **Movable** for dynamic time‑of‑day changes.

### 5.3 Rain Puddle Reflections
- Create a **Landscape Layer** for wet asphalt/rain puddles.
- Use a **Reflection Capture** actor to capture surrounding neon lights.
- Apply a **Material Blend** that increases specular and reduces roughness when wet.
- Use **Parallax Occlusion Mapping** to give puddles depth.

## Section 6: Project Structure

```
Content/
├── Landscapes/
│   ├── Materials/     # Landscape materials (M_CyberpunkTerrain, etc.)
│   ├── Layers/        # Layer textures (grass, rock, sand, mud, asphalt)
│   └── Heightmaps/    # Terrain heightmaps (cyberpunk_heightmap.png)
├── Foliage/
│   ├── Trees/         # Tree instanced meshes (cyberpunk trees, dead trunks)
│   ├── Rocks/         # Rock formations (concrete slabs, rubble)
│   └── Props/         # Street props (barrels, crates, neon signs, debris)
└── Lighting/
    └── Atmospheres/   # Sky/atmosphere presets (BP_Sky_Atmosphere, BP_HeightFog)
```

**Best Practices:**
- Keep landscape materials in `Landscapes/Materials/` for easy navigation.
- Store foliage meshes in subfolders by type (Trees, Rocks, Props).
- Use blueprint actors for complex lighting setups (e.g., `BP_NeonLight_Flicker`).
- Version‑control only source assets; derived assets (UE‑cooked) should be in `.gitignore`.

---

## MCP Tool Reference (Landscape & Foliage)

### Landscape Material Tools
| Tool | Description | Parameters |
|------|-------------|------------|
| `create_landscape_material` | Create a master landscape material with LayerBlend | `material_name`, `blend_mode`, `num_layers` |
| `add_landscape_material_layer` | Add a layer to a landscape material | `material_path`, `layer_index`, `diffuse_texture`, `normal_texture`, `roughness_texture`, `tiling` |
| `set_landscape_layer_blend_params` | Configure height‑blending between two layers | `material_path`, `layer_a_index`, `layer_b_index`, `blend_height`, `blend_falloff` |
| `apply_landscape_layer` | Apply a material layer to a landscape actor | `landscape_actor_name`, `material_path`, `layer_name` |
| `create_terrain_landscape` | Create a new ALandscape actor | `landscape_name`, `sections_per_component`, `section_size`, `sections_xy`, `location_x`, `location_y`, `location_z` |

### Foliage & Lighting Tools
| Tool | Description | Parameters |
|------|-------------|------------|
| `spawn_foliage_actor` | Spawn a single foliage static mesh | `mesh_path`, `location_x`, `location_y`, `location_z`, `rotation_yaw`, `rotation_pitch`, `rotation_roll`, `scale_x`, `scale_y`, `scale_z` |
| `paint_foliage_layer` | Paint mass foliage instances on landscape | `landscape_actor_name`, `mesh_path`, `paint_density`, `brush_radius`, `paint_strength`, `random_scale_min`, `random_scale_max`, `random_rotation` |
| `create_directional_light` | Create a directional light (sun/moon) | `light_name`, `intensity`, `color_r`, `color_g`, `color_b`, `rotation_yaw`, `rotation_pitch` |
| `setup_sky_atmosphere` | Configure sky atmosphere component | `sun_light_name`, `rayleigh_scattering_scale`, `mie_scattering_scale`, `ground_albedo_r`, `ground_albedo_g`, `ground_albedo_b` |
| `setup_height_fog` | Setup exponential height fog | `fog_density`, `fog_height_falloff`, `fog_inscattering_color_r`, `fog_inscattering_color_g`, `fog_inscattering_color_b`, `fog_max_opacity` |
| `import_terrain_heightmap` | Import heightmap for terrain | `landscape_actor_name`, `heightmap_image_path`, `heightmap_scale` |

---

## Next Steps
1. **Run the MCP server** (`uv run unreal_mcp_server_advanced.py`) and connect to Unreal Editor.
2. **Create a test landscape** using the terrain tools.
3. **Import a cyberpunk heightmap** (e.g., from World Machine).
4. **Build the material layers** with grass, rock, sand, mud, and asphalt.
5. **Paint foliage** (trees, rocks, debris) across the landscape.
6. **Set up lighting** (directional light, sky atmosphere, height fog).
7. **Iterate** based on visual feedback.

This pipeline enables rapid iteration for atomichearts’ cyberpunk environments, combining automated MCP tools with artistic direction.