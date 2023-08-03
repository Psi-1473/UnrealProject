// Fill out your copyright notice in the Description page of Project Settings.


#include "SevarogFire.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/Material.h"
#include "Components/BoxComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/MovementComponent.h"
#include "Particles/ParticleSystem.h"
#include "../../Creatures/Player/MyPlayer.h"
#include "Particles/ParticleSystemComponent.h"
#include "Engine/DamageEvents.h"
#include "../../DEFINE.h"
#include "Kismet/GameplayStatics.h"

ASevarogFire::ASevarogFire()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Script/Engine.StaticMesh'/Game/BigNiagaraBundle/NiagaraEffectMix3/ExampleContent/SM_MaterialSphere.SM_MaterialSphere'"));
	static ConstructorHelpers::FObjectFinder<UMaterial> MatAsset(TEXT("/Script/Engine.Material'/Game/ParagonSevarog/FX/Materials/Energy/M_SiphonSouls.M_SiphonSouls'"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> Explosion(TEXT("/Script/Engine.ParticleSystem'/Game/Realistic_Starter_VFX_Pack_Vol2/Particles/Explosion/P_Explosion_Big_B.P_Explosion_Big_B'"));
	if (MeshAsset.Succeeded())
		MeshComp->SetStaticMesh(MeshAsset.Object);
	if (MatAsset.Succeeded())
		MeshComp->SetMaterial(0, MatAsset.Object);
	if (MatAsset.Succeeded())
		ExplosionParticle = Explosion.Object;

	BoxCollider->SetRelativeScale3D(FVector(7.f, 7.f, 7.f));
	BoxCollider->SetCollisionProfileName(TEXT("InteractBox"));
	BoxCollider->SetRelativeScale3D(FVector(0.7f, 0.7f, 0.7f));
	ParticleComponent->SetRelativeScale3D(FVector(1.f, 1.f, 1.f));
	MeshComp->SetCollisionProfileName(TEXT("NoCollision"));
	BoxCollider->OnComponentBeginOverlap.AddDynamic(this, &ASevarogFire::OnOverlapBegin);
	BoxCollider->OnComponentEndOverlap.AddDynamic(this, &ASevarogFire::OnOverlapEnd);


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

void ASevarogFire::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(DestroyTimerHandle, this, &ASevarogFire::DestroyThis, 2.0f, false);
	GetWorldTimerManager().SetTimer(HitTimerHandler, this, &ASevarogFire::AttackTarget, 0.3f, true);

}

void ASevarogFire::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (TargetPlayer == nullptr)
		return;
	
	FVector PosToAdd = GetActorLocation() - PrevTargetPos;
	TargetPlayer->SetActorLocation(TargetPlayer->GetActorLocation() + PosToAdd);
	PrevTargetPos = GetActorLocation();
}

void ASevarogFire::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && (OtherActor != this))
	{
		auto Player = Cast<AMyPlayer>(OtherActor);
		if (Player)
		{
			TargetPlayer = Player;
			UE_LOG(LogTemp, Warning, TEXT("Sevarog Projectile Hit Player"));
			FDamageEvent DamageEvent;
			PrevTargetPos = GetActorLocation();
			TargetPlayer->SetState(STATE::IDLE);
			Player->SetState(STATE::PULLED);
			AttackTarget();
			//Enemy->TakeDamage(10, DamageEvent, OwnerPlayer->GetController(), OwnerPlayer);
		}
	}
}

void ASevarogFire::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	//if (OtherActor && (OtherActor != this))
	//{
	//	auto Player = Cast<AMyPlayer>(OtherActor);
	//	if (Player && Player == TargetPlayer)
	//	{
	//		TargetPlayer->SetState(STATE::IDLE);
	//		TargetPlayer = nullptr;
	//	}
	//}

}

void ASevarogFire::DestroyThis()
{
	FTransform Trans(GetActorLocation());
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionParticle, Trans);
	// 터지는 히트 판정 넣기
	// 폭발 구현
	Explode();
	Destroy();

}

void ASevarogFire::Explode()
{
	if (TargetPlayer == nullptr)
		return;

	UE_LOG(LogTemp, Warning, TEXT("Explode!"));
	FVector DirVector = TargetPlayer->GetActorLocation() - GetActorLocation();
	DirVector.Normalize();
	FVector Power = DirVector * 300.f;
	Power.Z = 700.f;
	TargetPlayer->LaunchCharacter(Power, true, true);
	FDamageEvent DamageEvent;
	TargetPlayer->OnDamaged(5.f, DamageEvent, Owner->GetInstigatorController(), Owner, AttackType::HITANDFALL);
}

void ASevarogFire::AttackTarget()
{
	if (TargetPlayer != nullptr)
	{
		FDamageEvent DamageEvent;
		TargetPlayer->OnDamaged(1.f, DamageEvent, Owner->GetInstigatorController(), Owner, AttackType::STRONG);
	}


}
