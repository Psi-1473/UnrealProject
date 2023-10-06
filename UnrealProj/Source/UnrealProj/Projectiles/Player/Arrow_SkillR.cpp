// Fill out your copyright notice in the Description page of Project Settings.


#include "Arrow_SkillR.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "../../Creatures/Player/MyPlayer.h"
#include "Kismet/GameplayStatics.h"
#include "../../Creatures/Monster/Monster.h"
#include "Engine/DamageEvents.h"
#include "../../Skills/EffectActor/SkillEffectActor.h"

AArrow_SkillR::AArrow_SkillR()
{
	ParticleComponent->SetRelativeLocation(FVector(0.f, 0.f, 190.f));
	ParticleComponent->SetRelativeScale3D(FVector(2.f, 1.f, 2.f));
	static ConstructorHelpers::FClassFinder<ASkillEffectActor> EffectActor(TEXT("/Script/Engine.Blueprint'/Game/02_Blueprints/SkillEffectActor/Player/1/BP_Effect_1_3.BP_Effect_1_3_C'"));

	if(EffectActor.Succeeded())
		Thunder = EffectActor.Class;

	MeshComp->SetStaticMesh(nullptr);
	MeshComp->SetRelativeScale3D(FVector(1.0f, 4.0f, 1.0f));

	BoxCollider->SetRelativeScale3D(FVector(6.0f, 2.5f, 4.f));
	BoxCollider->SetRelativeRotation(FRotator(0.f, 0.f, 0.f));
	BoxCollider->SetCollisionProfileName(TEXT("NoCollision"));
	MeshComp->SetCollisionProfileName(TEXT("NoCollision"));
	BoxCollider->OnComponentBeginOverlap.AddDynamic(this, &AArrow_SkillR::OnOverlapBegin);
	BoxCollider->OnComponentEndOverlap.AddDynamic(this, &AArrow_SkillR::OnOverlapEnd);


	RootComponent = BoxCollider;
	MeshComp->SetupAttachment(RootComponent);
	ParticleComponent->SetupAttachment(MeshComp);

	ProjectileMovementComponent->SetUpdatedComponent(BoxCollider);
	ProjectileMovementComponent->InitialSpeed = 4000.f;
	ProjectileMovementComponent->MaxSpeed = 0.f;
	ProjectileMovementComponent->bRotationFollowsVelocity = true;
	ProjectileMovementComponent->bShouldBounce = false;
	ProjectileMovementComponent->ProjectileGravityScale = 0.f;
	InitialLifeSpan = 0.5f;
}

void AArrow_SkillR::BeginPlay()
{
	Super::BeginPlay();
	auto MyPlayer = Cast<AMyPlayer>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	OwnerPlayer = MyPlayer;
}

void AArrow_SkillR::SpawnThunder(FVector SpawnLocation)
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = Cast<AActor>(OwnerPlayer);
	SpawnParams.Instigator = OwnerPlayer->GetInstigator();

	auto EffectActor = OwnerPlayer->GetWorld()->SpawnActor<ASkillEffectActor>(Thunder, SpawnLocation, GetActorRotation(), SpawnParams);
	EffectActor->SetOwner(Cast<AActor>(OwnerPlayer));
}

void AArrow_SkillR::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && (OtherActor != this))
	{
		auto Enemy = Cast<AMonster>(OtherActor);
		if (Enemy)
		{
			this->Destroy();
			FDamageEvent DamageEvent;
			if (OwnerPlayer == nullptr)
			{
				UE_LOG(LogTemp, Warning, TEXT("OWNER NULL"));
				return;
			}
			FVector ThunderLocation = Enemy->GetActorLocation();
			Enemy->TakeDamage(10, DamageEvent, OwnerPlayer->GetController(), OwnerPlayer);

			SpawnThunder(ThunderLocation);
			if (HitEffect != nullptr)
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitEffect, Enemy->GetActorLocation());

			
		}
	}
}

void AArrow_SkillR::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}

