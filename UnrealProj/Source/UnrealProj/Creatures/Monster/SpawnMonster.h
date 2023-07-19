// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Monster.h"
#include "SpawnMonster.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJ_API ASpawnMonster : public AMonster
{
	GENERATED_BODY()
public:
	ASpawnMonster();

public:
	TWeakObjectPtr<class AMonsterSpawner> GetSpawner() { return Spawner; }
	void SetSpawner(TWeakObjectPtr<class AMonsterSpawner> Value) { Spawner = Value; }

private:
	TWeakObjectPtr<class AMonsterSpawner> Spawner;
};
