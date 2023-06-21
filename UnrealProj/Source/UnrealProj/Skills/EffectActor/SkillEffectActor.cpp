// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillEffectActor.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "../../Creatures/Player/MyPlayer.h"
#include "NiagaraComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ASkillEffectActor::ASkillEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;
	ParticleComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("PARTICLE"));
	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("ROOT"));

	RootComponent = RootScene;
	ParticleComponent->SetupAttachment(RootScene);
}

void ASkillEffectActor::BeginPlay()
{
	Super::BeginPlay();
	auto MyPlayer = Cast<AMyPlayer>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	OwnerPlayer = MyPlayer;
}

void ASkillEffectActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


