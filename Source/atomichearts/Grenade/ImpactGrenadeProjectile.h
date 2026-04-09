// Copyright 2024 Destiny Cyberpunk

#pragma once

#include "CoreMinimal.h"
#include "Grenade/AGrenadeProjectile.h"
#include "ImpactGrenadeProjectile.generated.h"

/**
 * Impact grenade: explodes immediately on contact, dealing instant damage.
 */
UCLASS()
class ATOMICHEARTS_API AImpactGrenadeProjectile : public AGrenadeProjectile
{
	GENERATED_BODY()
	
public:
	AImpactGrenadeProjectile();

protected:
	virtual void ApplyEffects(const FVector& ExplosionLocation) override;
};