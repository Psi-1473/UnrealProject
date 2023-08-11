// Fill out your copyright notice in the Description page of Project Settings.


#include "SevarogFireball.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Engine/DamageEvents.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"
#include "../../DEFINE.h"
#include "../../Creatures/Player/MyPlayer.h"

ASevarogFireball::ASevarogFireball()
{
	static ConstructorHelpers::FObjectFinder<UParticleSystem> FIRE(TEXT("/Script/Engine.ParticleSystem'/Game/FXVarietyPack/Particles/P_ky_fireBall.P_ky_fireBall'"));
	if (FIRE.Succeeded())
		ParticleComponent->SetTemplate(FIRE.Object);

	BoxCollider->SetRelativeScale3D(FVector(7.f, 7.f, 7.f));
	BoxCollider->SetCollisionProfileName(TEXT("InteractBox"));
	BoxCollider->SetRelativeScale3D(FVector(1.5f, 1.5f, 1.5f));
	ParticleComponent->SetRelativeScale3D(FVector(1.f, 1.f, 1.f));
	MeshComp->SetCollisionProfileName(TEXT("NoCollision"));
	MeshComp->SetRelativeRotation(FRotator(90.f, 0.f, 0.f));
	BoxCollider->OnComponentBeginOverlap.AddDynamic(this, &ASevarogFireball::OnOverlapBegin);
	BoxCollider->OnComponentEndOverlap.AddDynamic(this, &ASevarogFireball::OnOverlapEnd);


	RootComponent = BoxCollider;
	MeshComp->SetupAttachment(RootComponent);
	ParticleComponent->SetupAttachment(MeshComp);

	ProjectileMovementComponent->SetUpdatedComponent(BoxCollider);
	ProjectileMovementComponent->InitialSpeed = 1200.f;
	ProjectileMovementComponent->MaxSpeed = 1200.f;
	ProjectileMovementComponent->bRotationFollowsVelocity = true;
	ProjectileMovementComponent->bShouldBounce = false;
	ProjectileMovementComponent->ProjectileGravityScale = 0.f;
	InitialLifeSpan = 3.f;
}

void ASevarogFireball::BeginPlay()
{
	Super::BeginPlay();
}

void ASevarogFireball::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASevarogFireball::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && (OtherActor != this))
	{
		auto Player = Cast<AMyPlayer>(OtherActor);
		if (Player)
		{
			UE_LOG(LogTemp, Warning, TEXT("Sevarog Fireball Hit Player"));
			FDamageEvent DamageEvent;
			Player->OnDamaged(10, DamageEvent, Owner->GetInstigatorController(), Owner, AttackType::STRONG);
			Destroy();
		}
	}
}

void ASevarogFireball::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

void ASevarogFireball::DestroyObj()
{
	// °´Ã¼ ÆÄ±«ÇÏ°í ÀÌÆåÆ®
	Destroy();
}
