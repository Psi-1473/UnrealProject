// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterSpawner.h"
#include <NavigationSystem.h>
#include "../Creatures/Monster/Monster.h"

AMonsterSpawner::AMonsterSpawner()
{
	PrimaryActorTick.bCanEverTick = true;

	//Monsters.Init(nullptr, MonsterActors.Num());
}

void AMonsterSpawner::BeginPlay()
{
	Super::BeginPlay();
	SpawnerLocation = GetActorLocation();

	Monsters.Init(nullptr, MonsterActors.Num());
	CheckSpawnTimer();
}

void AMonsterSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



AMonster* AMonsterSpawner::SpawnMonster(TSubclassOf<class AMonster> ActorToSpawn, FVector Location)
{
	FTransform SpawnTrans;
	SpawnTrans.SetLocation(Location);
	FActorSpawnParameters SpawnParam;
	SpawnParam.Owner = this;
	SpawnParam.Instigator = GetInstigator();
	SpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	AActor* Mob = GetWorld()->SpawnActor<AActor>(ActorToSpawn, SpawnTrans, SpawnParam);
	auto Monster = Cast<AMonster>(Mob);
	Monster->SetSpawner(this);

	return Monster;
}


 FVector AMonsterSpawner::FindSpawnSpot()
 {
 	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(GetWorld());
 
 	FNavLocation RandomLocation;
 
 	NavSystem->GetRandomPointInNavigableRadius(SpawnerLocation, 500.f, RandomLocation);
 	RandomLocation.Location.Z += 50;

 	return RandomLocation.Location;
 }

 void AMonsterSpawner::CheckSpawnTimer()
 {
	 int Number = Monsters.Num();
	 for (int i = 0; i < Number; i++)
	 {
		 if (Monsters[i] == nullptr)
		 {
			 Monsters[i] = SpawnMonster(MonsterActors[i], FindSpawnSpot());
		 }
	 }

	 GetWorldTimerManager().SetTimer(SpawnTimerHandle, this, &AMonsterSpawner::CheckSpawnTimer, 15.f, true);
 }


