// Copyright 2024 Destiny Cyberpunk

#include "SolarBurnZoneActor.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "TimerManager.h"

ASolarBurnZoneActor::ASolarBurnZoneActor()
{
	PrimaryActorTick.bCanEverTick = false;

	// Create zone sphere
	ZoneSphere = CreateDefaultSubobject<USphereComponent>(TEXT("ZoneSphere"));
	RootComponent = ZoneSphere;
	ZoneSphere->InitSphereRadius(ZoneRadius);
	ZoneSphere->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	ZoneSphere->SetGenerateOverlapEvents(true);

	// Create particle system (placeholder)
	BurnParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("BurnParticle"));
	BurnParticle->SetupAttachment(RootComponent);
	BurnParticle->bAutoActivate = true;
}

void ASolarBurnZoneActor::BeginPlay()
{
	Super::BeginPlay();
	StartBurning();
}

void ASolarBurnZoneActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	StopBurning();
	Super::EndPlay(EndPlayReason);
}

void ASolarBurnZoneActor::StartBurning()
{
	// Apply first burn immediately
	ApplyBurn();

	// Set up repeating burn timer
	if (BurnInterval > 0.f)
	{
		GetWorldTimerManager().SetTimer(BurnTimerHandle, this, &ASolarBurnZoneActor::ApplyBurn, BurnInterval, true);
	}

	// Set destruction timer
	if (BurnDuration > 0.f)
	{
		GetWorldTimerManager().SetTimer(DestroyTimerHandle, this, &ASolarBurnZoneActor::DestroyZone, BurnDuration, false);
	}

	UE_LOG(LogTemp, Log, TEXT("Solar burn zone created at %s, radius %f, duration %f"), *GetActorLocation().ToString(), ZoneRadius, BurnDuration);
}

void ASolarBurnZoneActor::StopBurning()
{
	GetWorldTimerManager().ClearTimer(BurnTimerHandle);
	GetWorldTimerManager().ClearTimer(DestroyTimerHandle);
}

void ASolarBurnZoneActor::SetZoneRadius(float NewRadius)
{
	ZoneRadius = NewRadius;
	if (ZoneSphere)
	{
		ZoneSphere->SetSphereRadius(ZoneRadius);
	}
}

void ASolarBurnZoneActor::ApplyBurn()
{
	TArray<AActor*> OverlappingActors;
	ZoneSphere->GetOverlappingActors(OverlappingActors);

	for (AActor* Actor : OverlappingActors)
	{
		// Skip self and owner
		if (Actor == this || Actor == GetOwner())
			continue;

		// Apply burn damage
		AController* InstigatorController = GetInstigatorController();
		UGameplayStatics::ApplyDamage(
			Actor,
			BurnDamage,
			InstigatorController ? InstigatorController : nullptr,
			this,
			nullptr
		);
	}

	UE_LOG(LogTemp, Log, TEXT("Solar burn zone at %s dealt %f damage to %d actors"), *GetActorLocation().ToString(), BurnDamage, OverlappingActors.Num());
}

void ASolarBurnZoneActor::DestroyZone()
{
	StopBurning();
	Destroy();
}