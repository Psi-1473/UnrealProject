// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerSkill_Bow_Third.h"
#include "../../../Creatures/Player/MyPlayer.h"
#include "../../../Animations/Player/PlayerAnim.h"
#include "../../../Items/Weapons/Weapon.h"
#include "../../../Projectiles/Projectile.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"

UPlayerSkill_Bow_Third::UPlayerSkill_Bow_Third()
{
	static ConstructorHelpers::FObjectFinder<UTexture2D> IMG(TEXT("/Script/Engine.Texture2D'/Game/09_Image/Skill/Arrow3.Arrow3'"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> HIT(TEXT("/Script/Engine.ParticleSystem'/Game/ParagonSparrow/FX/Particles/Sparrow/Abilities/Ultimate/FX/P_Sparrow_UltHit.P_Sparrow_UltHit'"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> Particle(TEXT("/Script/Engine.ParticleSystem'/Game/ParagonSparrow/FX/Particles/Sparrow/Abilities/Ultimate/FX/P_Sparrow_Burst.P_Sparrow_Burst'"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> Particle2(TEXT("/Script/Engine.ParticleSystem'/Game/ParagonSparrow/FX/Particles/Sparrow/Abilities/Ultimate/FX/P_SparrowBuff.P_SparrowBuff'"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> Particle3(TEXT("/Script/Engine.ParticleSystem'/Game/ParagonSparrow/FX/Particles/Sparrow/Abilities/Ultimate/FX/P_Sparrow_UltHit.P_Sparrow_UltHit'"));
	static ConstructorHelpers::FClassFinder<AProjectile> ARROW(TEXT("/Script/Engine.Blueprint'/Game/02_Blueprints/Projectiles/BP_Arrow_R.BP_Arrow_R_C'"));

	if (IMG.Succeeded()) Txt = IMG.Object;
	if (HIT.Succeeded()) HitEffect = HIT.Object;
	if (Particle.Succeeded()) PlayerParticle = Particle.Object;
	if (Particle2.Succeeded()) BowParticle = Particle2.Object;
	if (Particle3.Succeeded()) AttackParticle = Particle3.Object;
	if (ARROW.Succeeded()) Arrow = ARROW.Class;
}

void UPlayerSkill_Bow_Third::Execute(AActor* OwnerActor, bool bRangeAttack)
{
	Super::Execute(OwnerActor, bRangeAttack);

	if (RemainingTime > 0.f)
		return;

	if (WeaponType != OwnerPlayer->GetWeapon()->GetType())
		return;

	FRotator Rot = OwnerPlayer->GetActorRotation();
	SetDefaultValue();
	BowParticleComp = UGameplayStatics::SpawnEmitterAtLocation(OwnerPlayer->GetWorld(), BowParticle,
	OwnerPlayer->GetActorLocation() + OwnerPlayer->GetActorForwardVector() * 100.f + 
	OwnerPlayer->GetActorUpVector() * 50.f + 
	OwnerPlayer->GetActorRightVector() * 5.f,
	Rot,
	FVector(4.f, 5.f, 4.f)
	);
	OwnerPlayer->GetWorldTimerManager().SetTimer(EffectTimer, this, &UPlayerSkill_Bow_Third::ParticlePlay, 0.45f, true);

}

void UPlayerSkill_Bow_Third::PlayParticle(AActor* OwnerActor)
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = Cast<AActor>(OwnerPlayer);
	SpawnParams.Instigator = OwnerPlayer->GetInstigator();

	FVector CameraLocation;
	FRotator CameraRotation;
	OwnerPlayer->GetActorEyesViewPoint(CameraLocation, CameraRotation);
	CameraRotation.Pitch += 5.f;

	FRotator Rot = OwnerPlayer->GetActorRotation();

	FString Directory = TEXT("/Script/Engine.ParticleSystem'/Game/ParagonSparrow/FX/Particles/Sparrow/Abilities/Ultimate/FX/P_Arrow_Ultimate.P_Arrow_Ultimate'");
	UParticleSystem* Particle = LoadObject<UParticleSystem>(NULL, *Directory, NULL, LOAD_None, NULL);

	UGameplayStatics::SpawnEmitterAtLocation(OwnerPlayer->GetWorld(), AttackParticle, OwnerPlayer->GetActorLocation() + OwnerPlayer->GetActorUpVector() * 30.f);

	AProjectile* Projectile = OwnerPlayer->GetWorld()->SpawnActor<AProjectile>(Arrow,
		OwnerPlayer->GetActorLocation() + OwnerPlayer->GetActorUpVector() * 55 + OwnerPlayer->GetActorRightVector() * 15.f,
		Rot,
		SpawnParams);

	if (Projectile == nullptr)
		return;

	Projectile->SetAttackStrength(true);
	Projectile->SetOwner(OwnerActor);
	Projectile->SetHitEffect(HitEffect);
	Projectile->SetMaxSpeed(8000.f);
	Projectile->SetParticle(Particle);
	Projectile->FireInDirection(Projectile->GetActorForwardVector(), 2.f);
}

void UPlayerSkill_Bow_Third::ParticlePlay()
{
	EffectCnt++;
	if (EffectCnt >= 5)
	{
		EffectCnt = 0;
		BowParticleComp->DestroyComponent();
		OwnerPlayer->GetWorldTimerManager().ClearTimer(EffectTimer);
	}
	FVector Loc = OwnerPlayer->GetActorLocation();
	Loc.Z -= 80.f;
	UGameplayStatics::SpawnEmitterAtLocation(OwnerPlayer->GetWorld(), PlayerParticle, Loc);

}
