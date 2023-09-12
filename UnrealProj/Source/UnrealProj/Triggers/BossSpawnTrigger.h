// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BossSpawnTrigger.generated.h"

UCLASS()
class UNREALPROJ_API ABossSpawnTrigger : public AActor
{
	GENERATED_BODY()
	
public:	
	ABossSpawnTrigger();

protected:
	virtual void BeginPlay() override;

public:	
	UFUNCTION()
	virtual void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:

private:
	UPROPERTY()
	bool bActivated = false;

	UPROPERTY(EditAnywhere)
	class UBoxComponent* BoxComponent;


};
