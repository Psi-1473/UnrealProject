// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Interface/Poolable.h"
#include "Projectile.generated.h"

UCLASS()
class UNREALPROJ_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	AProjectile();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	void SetAttackStrength(bool Value);
	void FireInDirection(const FVector& ShootDirection, float Power);
	void SetParticle(class UParticleSystem* Value);
	void SetMaxSpeed(float Speed);

	void SetHitEffect(class UParticleSystem* Effect) { HitEffect = Effect; }

protected:
	UPROPERTY(EditAnywhere)
	bool bHeavyAttack = false;

	UPROPERTY(EditAnywhere)
		class UBoxComponent* BoxCollider;

	UPROPERTY(EditAnywhere)
		class UProjectileMovementComponent* ProjectileMovementComponent;

	UPROPERTY(EditAnywhere)
		class UStaticMeshComponent* MeshComp;

	UPROPERTY(EditAnywhere)
	class UParticleSystemComponent* ParticleComponent;

	UPROPERTY()
		class AMyPlayer* OwnerPlayer;

	UPROPERTY()
	class UParticleSystem* HitEffect;

};
