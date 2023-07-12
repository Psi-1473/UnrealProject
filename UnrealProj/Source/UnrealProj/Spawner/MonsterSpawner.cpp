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

	AActor* Mob = GetWorld()->SpawnActor<AActor>(ActorToSpawn, SpawnTrans);
	auto Monster = Cast<AMonster>(Mob);
	//if (Kwang == nullptr)
	//	return;
	//Kwang->SetSpawner(this);

	return Monster;
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
	 UE_LOG(LogTemp, Warning, TEXT("CHECK ! "));
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


