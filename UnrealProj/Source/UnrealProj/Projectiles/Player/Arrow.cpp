// Fill out your copyright notice in the Description page of Project Settings.


#include "Arrow.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"
#include "../../Creatures/Player/MyPlayer.h"
#include "Kismet/GameplayStatics.h"
#include "../../Creatures/Monster/Monster.h"
#include "Engine/DamageEvents.h"

AArrow::AArrow()
{
	ParticleComponent->SetRelativeLocation(FVector(20.f, 0.f, 0.f));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Script/Engine.StaticMesh'/Game/04_Mesh/Weapon/Arrow/Arrow.Arrow'"));

	if (MeshAsset.Succeeded())
		MeshComp->SetStaticMesh(MeshAsset.Object);
	MeshComp->SetRelativeScale3D(FVector(1.0f, 4.0f, 1.0f));

	BoxCollider->SetRelativeScale3D(FVector(1.0f, 0.25f, 0.25f));
	BoxCollider->SetRelativeRotation(FRotator(0.f, 0.f, 0.f));
	BoxCollider->SetCollisionProfileName(TEXT("NoCollision"));
	MeshComp->SetCollisionProfileName(TEXT("NoCollision"));
	BoxCollider->OnComponentBeginOverlap.AddDynamic(this, &AArrow::OnOverlapBegin);
	BoxCollider->OnComponentEndOverlap.AddDynamic(this, &AArrow::OnOverlapEnd);


	RootComponent = BoxCollider;
	MeshComp->SetupAttachment(RootComponent);
	ParticleComponent->SetupAttachment(MeshComp);

	ProjectileMovementComponent->SetUpdatedComponent(BoxCollider);
	ProjectileMovementComponent->InitialSpeed = 10000.f;
	ProjectileMovementComponent->MaxSpeed = 0.f;
	ProjectileMovementComponent->bRotationFollowsVelocity = true;
	ProjectileMovementComponent->bShouldBounce = false;
	InitialLifeSpan = 0.08f;
}
void AArrow::BeginPlay()
{
	Super::BeginPlay();
	auto MyPlayer = Cast<AMyPlayer>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	OwnerPlayer = MyPlayer;
}

void AArrow::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
void AArrow::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
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
			Enemy->OnDamaged(10, DamageEvent, OwnerPlayer->GetController(), OwnerPlayer);
			//UE_LOG(LogTemp, Warning, TEXT("%s"), Enemy->GetName());
			if (HitEffect != nullptr)
			{
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitEffect, Enemy->GetActorLocation());
			}
		}
	}
}

void AArrow::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}
