// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillEffectActor.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "NiagaraComponent.h"

// Sets default values
ASkillEffectActor::ASkillEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;
	ParticleComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("PARTICLE"));
	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("ROOT"));

	RootComponent = RootScene;
}

void ASkillEffectActor::BeginPlay()
{
	Super::BeginPlay();
	
}


