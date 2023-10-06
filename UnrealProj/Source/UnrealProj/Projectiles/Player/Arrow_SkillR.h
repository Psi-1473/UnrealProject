// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Projectile.h"
#include "Arrow_SkillR.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJ_API AArrow_SkillR : public AProjectile
{
	GENERATED_BODY()
	
public:
	AArrow_SkillR();
protected:
	virtual void BeginPlay() override;

	void SpawnThunder(FVector SpawnLocation);
public:
	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UPROPERTY()
	TSubclassOf<class ASkillEffectActor> Thunder; 
};
