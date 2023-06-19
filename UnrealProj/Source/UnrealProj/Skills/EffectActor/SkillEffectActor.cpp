// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillEffectActor.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/SceneComponent.h"

// Sets default values
ASkillEffectActor::ASkillEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;
	ParticleComponent = CreateDefaultSubobject<UParticleSystemComponent >(TEXT("PARTICLE"));
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
}

void ASkillEffectActor::BeginPlay()
{
	Super::BeginPlay();
	
}


