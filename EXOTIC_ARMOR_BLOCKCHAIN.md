# EXOTIC ARMOR & BLOCKCHAIN ITEM REGISTRY

---

## Part 1: EXOTIC ARMOR (10 per class = 60 total)

### Exotic vs Regular Armor

| Regular Armor | Exotic Armor |
|---------------|--------------|
| Stats + Perks | Stats + Perks + **Intrinsic Ability** |

Exotics introduce a **unique active/passive ability** per piece — setting them apart as chase loot.

---

### Tech Mage (10)

| # | Name | Intrinsic Ability |
|---|------|-------------------|
| 1 | CHRONO VISOR | Time Slow on grenade hit |
| 2 | TEMPORAL VEST | Rally barricade speeds allies |
| 3 | PHASE GLOVES | Dodge extends invisibility |
| 4 | WARP BOOTS | Blink charges abilities |
| 5 | FUTURE SIGHT | See through walls |
| 6 | TIME FLUX | Abilities affect multiple targets |
| 7 | PARADOX CAGE | Chance to reverse damage |
| 8 | CHRONO HARNESS | Ultimate recharges allies |
| 9 | WINDUP GEAR | Cooldowns tick faster when hit |
| 10 | INFINITY LOOP | Abilities chain to nearby enemies |

### Chrome Sentinel (10)

| # | Name | Intrinsic Ability |
|---|------|-------------------|
| 1 | IRON BANNER | Barricade grants overshield |
| 2 | TITAN CRUSH | Ground pound creates shockwave |
| 3 | FORTRESS MODE | Immobile but invincible |
| 4 | JUGGERNAUT | Constant overshield |
| 5 | RALLY POINT | Allies near barricade heal |
| 6 | EARTHQUAKE | Sprint triggers ground slam |
| 7 | BULWARK | Barricade lasts forever |
| 8 | UNSTOPPABLE | Cannot be staggered |
| 9 | MOUNTAIN KEEP | Massive HP buff |
| 10 | LAST STAND | Gain power when alone |

### Neon Phantom (10)

| # | Name | Intrinsic Ability |
|---|------|-------------------|
| 1 | QUICK DRAW | Instant weapon swap |
| 2 | FAN THE HAMMER | Rapid pistol fire |
| 3 | HOT PURSUIT | Move faster near enemies |
| 4 | EYES OPEN | Highlight enemies always |
| 5 | FRONTAL ASSAULT | Damage taken heals |
| 6 | PERFECT BALANCE | No accuracy loss |
| 7 | TRICKSTER | Enemies explode on death |
| 8 | BLITZ | Sprint leaves blinding trail |
| 9 | SIXTH SENSE | Detect nearby enemies |
| 10 | GUNSLINGER | Rapid precision kills buff |

### Ghost Runner (10)

| # | Name | Intrinsic Ability |
|---|------|-------------------|
| 1 | VANISH | Invisibility on demand |
| 2 | PHANTOM | Reduced enemy detection |
| 3 | BLACKOUT | Nearest enemy goes blind |
| 4 | STEALTH PATROL | No aggro while hidden |
| 5 | CLOAK AND DAGGER | Double jump from stealth |
| 6 | UNSEEN STRIKE | First attack from stealth crits |
| 7 | GHOST PROTOCOL | Disable nearby tech |
| 8 | SHADOW DANCE | Attacks grant brief invisibility |
| 9 | CAMO | Blend with environment |
| 10 | TRACKER | See enemy footprints |

### Solaris Warden (10)

| # | Name | Intrinsic Ability |
|---|------|-------------------|
| 1 | HEALING RIFT | Placeable healing zone |
| 2 | SOLAR FLARE | Buff ally damage |
| 3 | INNER LIGHT | Damage grants healing |
| 4 | SOLAR OVERFLOW | Abilities overheal |
| 5 | RISING DAWN | Kills create healing zones |
| 6 | RADIANT MANTLE | Allies near rift gain power |
| 7 | FIREFLY | Precision kills explode |
| 8 | WARMIND'S PROTECTION | Sentry drone |
| 9 | LIGHTBEARER | Resurrect grants brief invincibility |
| 10 | BENEVOLENCE | Healing increases ally damage |

---

### Intrinsic Ability System (Blueprint)

```cpp
UENUM(BlueprintType)
enum class EExoticIntrinsic : uint8
{
    None,

    // ── Tech Mage ──
    TimeSlowOnGrenade,
    RallyBarricadeSpeed,
    DodgeInvisExtend,
    BlinkChargesAbilities,
    SeeThroughWalls,
    AbilitiesChainTargets,
    ReverseDamageChance,
    UltimateRechargesAllies,
    CooldownTickOnHit,
    AbilitiesChainNearby,

    // ── Chrome Sentinel ──
    BarricadeGrantsOvershield,
    GroundPoundShockwave,
    FortressModeInvincible,
    ConstantOvershield,
    AlliesNearBarricadeHeal,
    SprintGroundSlam,
    BarricadeLastsForever,
    CannotBeStaggered,
    MassiveHPBuff,
    GainPowerWhenAlone,

    // ── Neon Phantom ──
    InstantWeaponSwap,
    RapidPistolFire,
    FasterNearEnemies,
    HighlightEnemiesAlways,
    DamageTakenHeals,
    NoAccuracyLoss,
    EnemiesExplodeOnDeath,
    SprintBlindingTrail,
    DetectNearbyEnemies,
    PrecisionKillsBuff,

    // ── Ghost Runner ──
    InvisibilityOnDemand,
    ReducedEnemyDetection,
    NearestEnemyGoesBlind,
    NoAggroWhileHidden,
    DoubleJumpFromStealth,
    StealthFirstAttackCrit,
    DisableNearbyTech,
    AttacksGrantBriefInvis,
    BlendWithEnvironment,
    SeeEnemyFootprints,

    // ── Solaris Warden ──
    PlaceableHealingZone,
    BuffAllyDamage,
    DamageGrantsHealing,
    AbilitiesOverheal,
    KillsCreateHealingZones,
    AlliesNearRiftGainPower,
    PrecisionKillsExplode,
    SentryDrone,
    ResurrectGrantsInvincibility,
    HealingIncreasesAllyDamage,

    Count
};
```

---

## Part 2: BLOCKCHAIN ITEM REGISTRY

### Why Blockchain?

- **Unique identification** — each item gets a verifiable token ID
- **Ownership verification** — on-chain record of who owns what
- **Decentralized trading** — no central server required for transfers
- **Anti-duplication** — smart contract enforces single ownership

### NFT-Based Item Model

Every weapon or armor piece is an NFT with on-chain + off-chain metadata:

```json
{
  "tokenId": "0x4a3b8f9e2d1c...",
  "owner": "0x7f2e4d1b9a3c...",
  "itemType": "armor",
  "itemClass": "TechMage",
  "exoticIndex": 5,
  "seed": 98765,
  "name": "FUTURE SIGHT",
  "rarity": "Exotic",
  "signatureTrait": "SeeThroughWalls",
  "perks": ["FastReload", "EnhancedGrip", "ThermalOptic"],
  "stats": {
    "defense": 85,
    "mobility": 72,
    "intellect": 90
  },
  "createdAt": "1712000000",
  "lastTradedAt": "1712100000",
  "price": "0"
}
```

### Token ID Generation

```
tokenId = keccak256(abi.encodePacked(seed, slotIndex, timestamp, creatorAddress))
```

Guarantees uniqueness even if the same seed/slot combo is used twice.

### Trading Smart Contract

```solidity
// SPDX-License-Identifier: MIT
pragma solidity ^0.8.24;

contract Trading {
    address public owner;
    uint256 public commissionRate = 30; // 30%

    mapping(uint256 => address) public itemOwners;
    mapping(uint256 => uint256) public itemPrices;

    event Trade(uint256 indexed tokenId, address from, address to, uint256 price);
    event PriceUpdate(uint256 indexed tokenId, uint256 newPrice);

    constructor() {
        owner = msg.sender;
    }

    function listItem(uint256 tokenId, uint256 price) external {
        require(itemOwners[tokenId] == msg.sender, "Not the owner");
        itemPrices[tokenId] = price;
        emit PriceUpdate(tokenId, price);
    }

    function tradeItem(uint256 tokenId) external payable {
        uint256 price = itemPrices[tokenId];
        require(price > 0, "Item not listed");
        require(msg.value >= price, "Insufficient payment");

        address seller = itemOwners[tokenId];
        uint256 commission = (price * commissionRate) / 100;
        uint256 payout = price - commission;

        itemOwners[tokenId] = msg.sender;
        itemPrices[tokenId] = 0;

        payable(seller).transfer(payout);
        emit Trade(tokenId, seller, msg.sender, price);
    }

    function mintItem(uint256 tokenId) external {
        require(itemOwners[tokenId] == address(0), "Already minted");
        itemOwners[tokenId] = msg.sender;
    }
}
```

### Wallet Integration

**Simple path (casual players):**
- Email/password registration
- Backend generates a wallet private key (encrypted)
- Key stored in user database, revealed on login

**Advanced path (Web3-native):**
- MetaMask browser extension
- WalletConnect for mobile wallets
- Sign messages for auth — no passwords needed

### Implementation Checklist

- [ ] `server/services/blockchain.js` — token ID generation, IPFS upload, registry queries
- [ ] `server/services/wallet.js` — wallet creation, key storage, signing
- [ ] `server/routes/trade.js` — list, buy, cancel endpoints
- [ ] `contracts/ItemRegistry.sol` — mint/burn, metadata pointer
- [ ] `contracts/Trading.sol` — trading logic with commission
- [ ] IPFS pinning service for item metadata JSON
- [ ] Frontend: wallet connect UI, marketplace listing

---

*Total lines (excluding this table): ~280*
