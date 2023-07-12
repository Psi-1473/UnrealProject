// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MonsterSpawner.generated.h"

UCLASS()
class UNREALPROJ_API AMonsterSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	AMonsterSpawner();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	void SpawnMonster(TSubclassOf<class AMonster> ActorToSpawn, FVector Location);
	void StartSpawnTimer();

private:
	FVector FindSpawnSpot();
	void CheckSpawnTimer();

private:
	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<class AMonster>> Monsters;




	UPROPERTY()
	FTimerHandle SpawnTimerHandle;
};
