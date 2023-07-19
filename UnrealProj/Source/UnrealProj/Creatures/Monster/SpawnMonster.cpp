// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnMonster.h"
#include "../../AI/MonsterAIController.h"

ASpawnMonster::ASpawnMonster()
{
	AIControllerClass = AMonsterAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}
