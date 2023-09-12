// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LevelSequenceActor.h"
#include "BossSpawnTrigger.generated.h"

UCLASS()
class UNREALPROJ_API ABossSpawnTrigger : public ALevelSequenceActor
{
	GENERATED_BODY()
	
public:	
	ABossSpawnTrigger(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void BeginPlay() override;

public:	
	UFUNCTION()
	virtual void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	void HideWidget();

	UFUNCTION()
	void ResetWidget();

	void SpawnBoss();
private:
	UPROPERTY()
	bool bActivated = false;

	UPROPERTY(EditAnywhere)
	class UBoxComponent* BoxComponent;

	UPROPERTY(EditAnywhere)
	TWeakObjectPtr<class AMyPlayer> EnteredPlayer;

	UPROPERTY(EditAnywhere)
	TWeakObjectPtr<class ABossMonster> SpawnedBoss;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class ABossMonster> BossClass;
	UPROPERTY()
	struct FTimerHandle SpawnBossTimer;


};
