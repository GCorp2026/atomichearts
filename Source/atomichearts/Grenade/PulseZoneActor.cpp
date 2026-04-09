// Copyright 2024 Destiny Cyberpunk

#include "PulseZoneActor.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "TimerManager.h"
#include "Net/UnrealNetwork.h"

APulseZoneActor::APulseZoneActor()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;

	// Create zone sphere
	ZoneSphere = CreateDefaultSubobject<USphereComponent>(TEXT("ZoneSphere"));
	RootComponent = ZoneSphere;
	ZoneSphere->InitSphereRadius(ZoneRadius);
	ZoneSphere->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	ZoneSphere->SetGenerateOverlapEvents(true);

	// Create particle system (placeholder)
	PulseParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("PulseParticle"));
	PulseParticle->SetupAttachment(RootComponent);
	PulseParticle->bAutoActivate = true;
}

void APulseZoneActor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(APulseZoneActor, PulseDamage);
	DOREPLIFETIME(APulseZoneActor, ZoneRadius);
	DOREPLIFETIME(APulseZoneActor, PulseInterval);
	DOREPLIFETIME(APulseZoneActor, ZoneDuration);
}

void APulseZoneActor::BeginPlay()
{
	Super::BeginPlay();
	StartPulsing();
}

void APulseZoneActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	StopPulsing();
	Super::EndPlay(EndPlayReason);
}

void APulseZoneActor::StartPulsing()
{
	// Apply first pulse immediately
	ApplyPulse();

	// Set up repeating pulse timer
	if (PulseInterval > 0.f)
	{
		GetWorldTimerManager().SetTimer(PulseTimerHandle, this, &APulseZoneActor::ApplyPulse, PulseInterval, true);
	}

	// Set destruction timer
	if (ZoneDuration > 0.f)
	{
		GetWorldTimerManager().SetTimer(DestroyTimerHandle, this, &APulseZoneActor::DestroyZone, ZoneDuration, false);
	}

	UE_LOG(LogTemp, Log, TEXT("Pulse zone created at %s, radius %f, duration %f"), *GetActorLocation().ToString(), ZoneRadius, ZoneDuration);
}

void APulseZoneActor::StopPulsing()
{
	GetWorldTimerManager().ClearTimer(PulseTimerHandle);
	GetWorldTimerManager().ClearTimer(DestroyTimerHandle);
}

void APulseZoneActor::SetZoneRadius(float NewRadius)
{
	ZoneRadius = NewRadius;
	if (ZoneSphere)
	{
		ZoneSphere->SetSphereRadius(ZoneRadius);
	}
}

void APulseZoneActor::ApplyPulse()
{
	TArray<AActor*> OverlappingActors;
	ZoneSphere->GetOverlappingActors(OverlappingActors);

	for (AActor* Actor : OverlappingActors)
	{
		// Skip self and owner
		if (Actor == this || Actor == GetOwner())
			continue;

		// Apply damage
		AController* InstigatorController = GetInstigatorController();
		UGameplayStatics::ApplyDamage(
			Actor,
			PulseDamage,
			InstigatorController ? InstigatorController : nullptr,
			this,
			nullptr
		);
	}

	UE_LOG(LogTemp, Log, TEXT("Pulse zone at %s dealt %f damage to %d actors"), *GetActorLocation().ToString(), PulseDamage, OverlappingActors.Num());
}

void APulseZoneActor::DestroyZone()
{
	StopPulsing();
	Destroy();
}