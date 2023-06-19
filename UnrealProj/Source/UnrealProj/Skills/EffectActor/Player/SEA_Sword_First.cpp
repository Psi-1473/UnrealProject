// Fill out your copyright notice in the Description page of Project Settings.


#include "SEA_Sword_First.h"
#include "Components/BoxComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Engine/DamageEvents.h"
#include "../../../Creatures/Monster/Monster.h"
#include "../../../Creatures/Player/MyPlayer.h"
#include "Kismet/GameplayStatics.h"

ASEA_Sword_First::ASEA_Sword_First()
{
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BOXCOMPONENT"));
	
	static ConstructorHelpers::FObjectFinder<UParticleSystem> PA(TEXT("/Script/Engine.ParticleSystem'/Game/ParagonAurora/FX/Particles/Abilities/Freeze/FX/P_Aurora_Freeze_Segment.P_Aurora_Freeze_Segment'"));
	if (PA.Succeeded())
		ParticleComponent->SetTemplate(PA.Object);
	BoxComponent->SetRelativeScale3D(FVector(2.4f, 2.0f, 2.f));
	BoxComponent->SetCollisionProfileName("Arrow");
}

void ASEA_Sword_First::BeginPlay()
{
	auto MyPlayer = Cast<AMyPlayer>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	OwnerPlayer = MyPlayer;

	FTimerDelegate TimeCallback;
	TimeCallback.BindLambda([this] {
		this->Destroy();
		GetWorldTimerManager().ClearTimer(DestroyTimerHandle);
		});
	GetWorldTimerManager().SetTimer(DestroyTimerHandle, TimeCallback, 1.f, false);
}

void ASEA_Sword_First::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && (OtherActor != this))
	{
		auto Enemy = Cast<AMonster>(OtherActor);
		if (Enemy)
		{
			FDamageEvent DamageEvent;
			if (OwnerPlayer == nullptr)
			{
				UE_LOG(LogTemp, Warning, TEXT("OWNER NULL"));
				return;
			}
			Enemy->TakeDamage(10, DamageEvent, OwnerPlayer->GetController(), OwnerPlayer);
		}
	}
}
