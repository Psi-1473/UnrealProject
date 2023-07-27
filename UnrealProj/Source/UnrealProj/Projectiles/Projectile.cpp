// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Engine/DamageEvents.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"

AProjectile::AProjectile()
{
	PrimaryActorTick.bCanEverTick = true;
	
	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	ParticleComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleComponent"));
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));

}


void AProjectile::BeginPlay()
{
	Super::BeginPlay();
}

void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AProjectile::SetAttackStrength(bool Value)
{
	bHeavyAttack = Value;
	BoxCollider->SetCollisionProfileName(TEXT("Arrow"));
}

void AProjectile::FireInDirection(const FVector& ShootDirection, float Power = 1.f)
{
	ProjectileMovementComponent->Velocity = ShootDirection * ProjectileMovementComponent->InitialSpeed * Power;
}

void AProjectile::SetParticle(UParticleSystem* Value)
{
	ParticleComponent->SetTemplate(Value);
}

void AProjectile::SetMaxSpeed(float Speed)
{
	ProjectileMovementComponent->MaxSpeed = Speed;
}

