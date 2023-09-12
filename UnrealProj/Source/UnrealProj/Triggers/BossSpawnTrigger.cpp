// Fill out your copyright notice in the Description page of Project Settings.


#include "BossSpawnTrigger.h"
#include "../Creatures/Player/MyPlayer.h"
#include "Components/BoxComponent.h"

ABossSpawnTrigger::ABossSpawnTrigger()
{
	PrimaryActorTick.bCanEverTick = false;
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoxComponent->SetCollisionProfileName("InteractBox");

	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ABossSpawnTrigger::OnOverlapBegin);
}

void ABossSpawnTrigger::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABossSpawnTrigger::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Triger Enter Active"));
	if (bActivated)
		return;

	if (OtherActor)
	{
		auto Player = Cast<AMyPlayer>(OtherActor);
		if (Player)
		{
			// bActivated = true;
			UE_LOG(LogTemp, Warning, TEXT("Player Enter!"));
			// 1. 시네마틱 재생
			// 2. 보스 소환
			// 3. 보스 Hp Widget 팝업
		}
	}
}


