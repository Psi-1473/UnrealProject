// Fill out your copyright notice in the Description page of Project Settings.


#include "SevarogFireball.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Engine/DamageEvents.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"

ASevarogFireball::ASevarogFireball()
{
	static ConstructorHelpers::FObjectFinder<UParticleSystem> FIRE(TEXT("/Script/Engine.ParticleSystem'/Game/FXVarietyPack/Particles/P_ky_fireBall.P_ky_fireBall'"));
	if (FIRE.Succeeded())
		ParticleComponent->SetTemplate(FIRE.Object);

	BoxCollider->SetRelativeScale3D(FVector(7.f, 7.f, 7.f));
	BoxCollider->SetCollisionProfileName(TEXT("InteractBox"));
	BoxCollider->SetRelativeScale3D(FVector(0.7f, 0.7f, 0.7f));
	ParticleComponent->SetRelativeScale3D(FVector(1.f, 1.f, 1.f));
	MeshComp->SetCollisionProfileName(TEXT("NoCollision"));
	MeshComp->SetRelativeRotation(FRotator(90.f, 0.f, 0.f));
	BoxCollider->OnComponentBeginOverlap.AddDynamic(this, &ASevarogFireball::OnOverlapBegin);
	BoxCollider->OnComponentEndOverlap.AddDynamic(this, &ASevarogFireball::OnOverlapEnd);


	RootComponent = BoxCollider;
	MeshComp->SetupAttachment(RootComponent);
	ParticleComponent->SetupAttachment(MeshComp);

	ProjectileMovementComponent->SetUpdatedComponent(BoxCollider);
	ProjectileMovementComponent->InitialSpeed = 800.f;
	ProjectileMovementComponent->MaxSpeed = 800.f;
	ProjectileMovementComponent->bRotationFollowsVelocity = true;
	ProjectileMovementComponent->bShouldBounce = false;
	ProjectileMovementComponent->ProjectileGravityScale = 0.f;
	InitialLifeSpan = 0.f;
}

void ASevarogFireball::BeginPlay()
{
}

void ASevarogFireball::Tick(float DeltaTime)
{
}

void ASevarogFireball::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

void ASevarogFireball::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}
