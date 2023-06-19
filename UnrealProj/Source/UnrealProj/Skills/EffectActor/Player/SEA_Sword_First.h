// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../SkillEffectActor.h"
#include "SEA_Sword_First.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJ_API ASEA_Sword_First : public ASkillEffectActor
{
	GENERATED_BODY()
	
public:
	ASEA_Sword_First();
protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	UPROPERTY()
	class UBoxComponent* BoxComponent;
	UPROPERTY()
	class AMyPlayer* OwnerPlayer;

	UPROPERTY()
	FTimerHandle DestroyTimerHandle;
};
