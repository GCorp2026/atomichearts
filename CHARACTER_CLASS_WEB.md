# Character Class Web Management System — atomicsoul.dzenbliss.com

## Overview

Web-based admin panel for managing Destiny Cyberpunk character classes, abilities, and player character unlocks.

---

## Tech Stack

| Layer | Technology |
|-------|------------|
| Frontend | React 18 + Vite + Tailwind CSS + lucide-react |
| Backend | Node.js + Express |
| Auth | JWT (existing middleware) |
| Database | JSON files (`server/data/*.json`) |
| Ports | Server: 3001, Frontend dev: 5173 |

---

## 1. Character Class API

### Endpoints

| Method | Path | Description |
|--------|------|-------------|
| GET | `/api/classes` | List all classes |
| POST | `/api/classes` | Create new class |
| GET | `/api/classes/:id` | Get single class |
| PUT | `/api/classes/:id` | Update class |
| DELETE | `/api/classes/:id` | Soft delete (set `enabled: false`) |
| POST | `/api/classes/:id/enable` | Enable class |
| POST | `/api/classes/:id/disable` | Disable class |

### Class Schema

```json
{
  "id": "uuid-v4",
  "name": "Tech Mage",
  "slug": "tech-mage",
  "subclass": "Chronokeeper",
  "description": "Time-bending mage with crowd control abilities",
  "abilities": [
    { "id": "uuid", "name": "Time Stop", "cooldown": 60, "ultimate": true },
    { "id": "uuid", "name": "Time Slow", "cooldown": 15, "ultimate": false },
    { "id": "uuid", "name": "Chrono Trap", "cooldown": 20, "ultimate": false },
    { "id": "uuid", "name": "Phase Shift", "cooldown": 10, "ultimate": false }
  ],
  "stats": {
    "primary": "Intelligence",
    "secondary": "ChronoPower"
  },
  "statsDescription": {
    "primary": "Skill damage",
    "secondary": "Ultimate charge rate"
  },
  "role": "Crowd Control / Support / Utility",
  "weaponTypes": ["PulseRifle", "TraceRifle"],
  "perks": ["Temporal Anchor", "Time Dilation", "Phase Walk"],
  "enabled": true,
  "createdAt": "ISO-8601",
  "updatedAt": "ISO-8601"
}
```

---

## 2. Account-Character Linking

### Endpoints

| Method | Path | Description |
|--------|------|-------------|
| GET | `/api/account/characters` | Get player's unlocked characters (max 3) |
| POST | `/api/account/characters` | Unlock character (validates max 3) |
| DELETE | `/api/account/characters/:id` | Remove character from account |

### AccountCharacter Schema

```json
{
  "id": "uuid-v4",
  "accountId": "uuid-v4",
  "classId": "uuid-v4",
  "unlockedAt": "ISO-8601"
}
```

### Max 3 Enforcement

```typescript
// POST /api/account/characters
const accountChars = await db.accountCharacters.findMany({ accountId });
if (accountChars.length >= 3) {
  return res.status(400).json({ error: "Maximum 3 characters per account" });
}
```

---

## 3. File Structure

```
atomicsoul-assets/
├── server/
│   ├── routes/
│   │   ├── classes.js          # Class CRUD endpoints
│   │   └── accountCharacters.js # Player character management
│   ├── data/
│   │   ├── classes.json         # Class definitions
│   │   └── accountCharacters.json
│   ├── middleware/
│   │   └── auth.js             # JWT verification (exists)
│   └── index.js                # Main server (add new routes)
├── src/
│   ├── pages/
│   │   └── ClassManagement.tsx  # Main admin page
│   ├── components/
│   │   ├── ClassList.tsx       # Grid of class cards
│   │   ├── ClassCard.tsx        # Individual class display
│   │   ├── ClassEditor.tsx      # Create/edit form
│   │   └── AbilityEditor.tsx    # Ability list editor
│   ├── hooks/
│   │   └── useClasses.ts       # API hooks
│   ├── types/
│   │   └── class.ts            # TypeScript interfaces
│   └── App.tsx                 # Add /classes route
```

---

## 4. Frontend Components

### ClassManagement.tsx
- Full admin page with class list + editor panel
- Toggle between list view and create/edit form
- Search/filter classes

### ClassList.tsx
- Responsive grid of ClassCard components
- Status badges (enabled/disabled)
- Quick action buttons (edit, toggle, delete)

### ClassCard.tsx
- Class name, subclass, role
- Ability icons with cooldown display
- Enabled/disabled toggle
- Edit button

### ClassEditor.tsx
- Form fields: name, slug, subclass, description, role
- Stats editor (primary/secondary with descriptions)
- Weapon types multiselect
- Perks list editor
- Ability list via AbilityEditor

### AbilityEditor.tsx
- Add/remove/reorder abilities
- Fields: name, cooldown, ultimate flag
- Visual distinction for ultimate abilities

---

## 5. Implementation Priority

1. **Backend: classes.json + routes** — Core CRUD
2. **Backend: accountCharacters** — Player linking
3. **Frontend: types + hooks** — Shared contracts
4. **Frontend: ClassList + ClassCard** — Read-only view
5. **Frontend: ClassEditor + AbilityEditor** — Write operations
6. **Frontend: ClassManagement page** — Full integration

---

## 6. Sample Data (Initial Classes)

```json
[
  {
    "id": "class-tech-mage",
    "name": "Tech Mage",
    "slug": "tech-mage",
    "subclass": "Chronokeeper",
    "role": "Crowd Control / Support",
    "abilities": [
      { "id": "ab1", "name": "Time Stop", "cooldown": 60, "ultimate": true },
      { "id": "ab2", "name": "Time Slow", "cooldown": 15, "ultimate": false },
      { "id": "ab3", "name": "Chrono Trap", "cooldown": 20, "ultimate": false },
      { "id": "ab4", "name": "Phase Shift", "cooldown": 10, "ultimate": false }
    ],
    "stats": { "primary": "Intelligence", "secondary": "ChronoPower" },
    "weaponTypes": ["PulseRifle", "TraceRifle"],
    "perks": ["Temporal Anchor", "Time Dilation", "Phase Walk"],
    "enabled": true
  },
  {
    "id": "class-chrome-sentinel",
    "name": "Chrome Sentinel",
    "slug": "chrome-sentinel",
    "subclass": "Iron Wall",
    "role": "Tank / Protector",
    "abilities": [
      { "id": "ab5", "name": "Barricade", "cooldown": 25, "ultimate": false },
      { "id": "ab6", "name": "Rally Shield", "cooldown": 30, "ultimate": false },
      { "id": "ab7", "name": "Ground Pound", "cooldown": 45, "ultimate": true },
      { "id": "ab8", "name": "Overshield", "cooldown": 20, "ultimate": false }
    ],
    "stats": { "primary": "Resilience", "secondary": "Armor" },
    "weaponTypes": ["HeavyWeapon", "Shotgun", "Sword"],
    "perks": ["Unyielding", "Last Stand", "Iron Will"],
    "enabled": true
  },
  {
    "id": "class-neon-phantom",
    "name": "Neon Phantom",
    "slug": "neon-phantom",
    "subclass": "Quickdraw",
    "role": "DPS / Flanker",
    "abilities": [
      { "id": "ab9", "name": "Fan the Hammer", "cooldown": 12, "ultimate": false },
      { "id": "ab10", "name": "Dodge", "cooldown": 8, "ultimate": false },
      { "id": "ab11", "name": "Marked for Death", "cooldown": 25, "ultimate": false },
      { "id": "ab12", "name": "Gun Kata", "cooldown": 40, "ultimate": true }
    ],
    "stats": { "primary": "Mobility", "secondary": "Precision" },
    "weaponTypes": ["HandCannon", "SMG", "Sidearm"],
    "perks": ["Hot Pursuit", "Eyes Open", "Frontal Assault"],
    "enabled": true
  },
  {
    "id": "class-ghost-runner",
    "name": "Ghost Runner",
    "slug": "ghost-runner",
    "subclass": "Shadow",
    "role": "Infiltrator / Recon",
    "abilities": [
      { "id": "ab13", "name": "Vanish", "cooldown": 35, "ultimate": false },
      { "id": "ab14", "name": "Scout Drone", "cooldown": 20, "ultimate": false },
      { "id": "ab15", "name": "Blink", "cooldown": 10, "ultimate": false },
      { "id": "ab16", "name": "EMP Burst", "cooldown": 50, "ultimate": true }
    ],
    "stats": { "primary": "Stealth", "secondary": "Tech" },
    "weaponTypes": ["ScoutRifle", "SuppressedSMG", "TraceRifle"],
    "perks": ["Ghost Protocol", "Unseen Strike", "Blackout"],
    "enabled": true
  },
  {
    "id": "class-solaris-warden",
    "name": "Solaris Warden",
    "slug": "solaris-warden",
    "subclass": "Lightbearer",
    "role": "Support / Healer",
    "abilities": [
      { "id": "ab17", "name": "Healing Rift", "cooldown": 18, "ultimate": false },
      { "id": "ab18", "name": "Solar Grenade", "cooldown": 22, "ultimate": false },
      { "id": "ab19", "name": "Revival", "cooldown": 60, "ultimate": false },
      { "id": "ab20", "name": "Solar Flare", "cooldown": 45, "ultimate": true }
    ],
    "stats": { "primary": "Restoration", "secondary": "Radiance" },
    "weaponTypes": ["AutoRifle", "PulseRifle", "Sidearm"],
    "perks": ["Inner Light", "Solar Overflow", "Rising Dawn"],
    "enabled": true
  }
]
```

---

## 7. Auth & Permissions

- All endpoints require valid JWT in `Authorization: Bearer <token>` header
- Use existing `server/middleware/auth.js`
- Admin role check for class write operations
- Account ID extracted from JWT for player character operations
