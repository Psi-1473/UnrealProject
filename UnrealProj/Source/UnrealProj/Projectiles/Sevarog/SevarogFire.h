// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Projectile.h"
#include "SevarogFire.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJ_API ASevarogFire : public AProjectile
{
	GENERATED_BODY()

public:
	ASevarogFire();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void DestroyThis();
private:
	UPROPERTY()
	TWeakObjectPtr<class AMyPlayer> TargetPlayer;

	UPROPERTY()
	struct FTimerHandle DestroyTimerHandle;

	UPROPERTY()
	FVector PrevTargetPos;

	UPROPERTY(EditAnywhere)
	class UParticleSystem* ExplosionParticle;
};
