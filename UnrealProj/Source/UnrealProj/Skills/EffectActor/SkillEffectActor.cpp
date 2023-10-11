// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillEffectActor.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "../../Creatures/Player/MyPlayer.h"
#include "NiagaraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/AudioComponent.h"

// Sets default values
ASkillEffectActor::ASkillEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;
	ParticleComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NIAGARA"));
	LegacyParticleComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("PARTICLE"));
	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AUDIO"));
	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("ROOT"));

	RootComponent = RootScene;
	ParticleComponent->SetupAttachment(RootComponent);
	LegacyParticleComponent->SetupAttachment(RootComponent);
	AudioComponent->SetupAttachment(RootComponent);

	ParticleComponent->SetCollisionProfileName(TEXT("NoCollision"));
	LegacyParticleComponent->SetCollisionProfileName(TEXT("NoCollision"));
}

void ASkillEffectActor::BeginPlay()
{
	Super::BeginPlay();
}

void ASkillEffectActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


