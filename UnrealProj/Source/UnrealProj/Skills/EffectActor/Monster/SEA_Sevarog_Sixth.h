// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../SkillEffectActor.h"
#include "SEA_Sevarog_Sixth.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJ_API ASEA_Sevarog_Sixth : public ASkillEffectActor
{
	GENERATED_BODY()
	
public:
	ASEA_Sevarog_Sixth();
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void HitPlayer();
private:
	UPROPERTY(EditAnywhere)
	class UCapsuleComponent* CapsuleComponent;

	UPROPERTY(EditAnywhere)
	class UParticleSystem* HitParticle;

	UPROPERTY()
	TWeakObjectPtr<class AMyPlayer> TargetPlayer;

	UPROPERTY()
	struct FTimerHandle HitTickTimer;
};
