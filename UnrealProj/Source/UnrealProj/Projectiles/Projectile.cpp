// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include <UnrealProj/Creatures/Monster/Monster.h>
#include "Engine/DamageEvents.h"
#include "Kismet/GameplayStatics.h"
#include "../Creatures/Player/MyPlayer.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"

AProjectile::AProjectile()
{
	PrimaryActorTick.bCanEverTick = true;
	
	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	ParticleComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleComponent"));
	ParticleComponent->SetRelativeLocation(FVector(20.f, 0.f, 0.f));

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Script/Engine.StaticMesh'/Game/04_Mesh/Weapon/Arrow/Arrow.Arrow'"));

	if (MeshAsset.Succeeded())
		MeshComp->SetStaticMesh(MeshAsset.Object);
	MeshComp->SetRelativeScale3D(FVector(1.0f, 4.0f, 1.0f));

	BoxCollider->SetRelativeScale3D(FVector(1.0f, 0.25f, 0.25f));
	BoxCollider->SetRelativeRotation(FRotator(0.f, 0.f, 0.f));
	BoxCollider->SetCollisionProfileName(TEXT("NoCollision"));
	MeshComp->SetCollisionProfileName(TEXT("NoCollision"));
	BoxCollider->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::OnOverlapBegin);
	BoxCollider->OnComponentEndOverlap.AddDynamic(this, &AProjectile::OnOverlapEnd);


	RootComponent = BoxCollider;
	MeshComp->SetupAttachment(RootComponent);
	ParticleComponent->SetupAttachment(MeshComp);

	ProjectileMovementComponent->SetUpdatedComponent(BoxCollider);
	ProjectileMovementComponent->InitialSpeed = 6000.f;
	ProjectileMovementComponent->MaxSpeed = 0.f;
	ProjectileMovementComponent->bRotationFollowsVelocity = true;
	ProjectileMovementComponent->bShouldBounce = false;
	InitialLifeSpan = 0.5f;
}

void AProjectile::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && (OtherActor != this))
	{
		auto Enemy = Cast<AMonster>(OtherActor);
		if (Enemy)
		{
			if (bHeavyAttack == false)
				this->Destroy();
			FDamageEvent DamageEvent;
			if (OwnerPlayer == nullptr)
			{
				UE_LOG(LogTemp, Warning, TEXT("OWNER NULL"));
				return;
			}
			Enemy->TakeDamage(10, DamageEvent, OwnerPlayer->GetController(), OwnerPlayer);
		}
	}
}

void AProjectile::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	auto MyPlayer = Cast<AMyPlayer>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	OwnerPlayer = MyPlayer;
	
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

