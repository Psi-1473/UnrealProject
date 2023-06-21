// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../SkillEffectActor.h"
#include "SEA_Sword_SecondDash.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJ_API ASEA_Sword_SecondDash : public ASkillEffectActor
{
	GENERATED_BODY()
	
public:
	ASEA_Sword_SecondDash();

protected:
	virtual void BeginPlay() override;
public:
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
private:
	UPROPERTY(EditAnywhere)
	class UCapsuleComponent* CapsuleComponent;

	UPROPERTY(EditAnywhere)
	class UParticleSystem* GroundParticle;
};
