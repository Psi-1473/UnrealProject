// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterSpawner.h"
#include <NavigationSystem.h>
#include "../Creatures/Monster/Monster.h"

AMonsterSpawner::AMonsterSpawner()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AMonsterSpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMonsterSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



void AMonsterSpawner::SpawnMonster(TSubclassOf<class AMonster> ActorToSpawn, FVector Location)
{
	FTransform SpawnTrans;
	SpawnTrans.SetLocation(Location);

	AActor* Mob = GetWorld()->SpawnActor<AActor>(ActorToSpawn, SpawnTrans);
	//auto Kwang = Cast<ASpawnMonster>(Mob);
	//if (Kwang == nullptr)
	//	return;
	//Kwang->SetSpawner(this);
}

void AMonsterSpawner::StartSpawnTimer()
{

}


 FVector AMonsterSpawner::FindSpawnSpot()
 {
 	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(GetWorld());
 
 	FNavLocation RandomLocation;
 
 	NavSystem->GetRandomPointInNavigableRadius(GetActorTransform().GetLocation(), 500.f, RandomLocation);
 	RandomLocation.Location.Z += 50;
 	return RandomLocation.Location;
 }

 void AMonsterSpawner::CheckSpawnTimer()
 {
 }


