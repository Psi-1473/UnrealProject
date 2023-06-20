// Fill out your copyright notice in the Description page of Project Settings.


#include "SEA_Sword_First.h"
#include "Components/CapsuleComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Engine/DamageEvents.h"
#include "../../../Creatures/Monster/Monster.h"
#include "../../../Creatures/Player/MyPlayer.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"


ASEA_Sword_First::ASEA_Sword_First()
{
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CAPSULE"));
	
	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> PA(TEXT("/Script/Niagara.NiagaraSystem'/Game/ParagonAurora/FX/Particles/Abilities/Freeze/FX/P_Aurora_Freeze_Segment_Converted.P_Aurora_Freeze_Segment_Converted'"));
	if (PA.Succeeded())
		ParticleComponent->SetAsset(PA.Object);
	CapsuleComponent->SetRelativeScale3D(FVector(2.f, 2.f, 2.f));
	CapsuleComponent->SetCapsuleHalfHeight(80.f, false);
	CapsuleComponent->SetCapsuleRadius(50.f, false);
	CapsuleComponent->SetCollisionProfileName("Arrow");
	CapsuleComponent->OnComponentBeginOverlap.AddDynamic(this, &ASEA_Sword_First::OnOverlapBegin);
	ParticleComponent->SetupAttachment(RootComponent);
	ParticleComponent->SetRelativeScale3D(FVector(1.5f, 2.5f, 4.5f));
	ParticleComponent->SetCollisionProfileName("NoCollision");
	CapsuleComponent->SetupAttachment(RootComponent);
	ParticleComponent->SetupAttachment(RootComponent);
	CapsuleComponent->SetRelativeRotation(FRotator(0.f, 0.f, 90.f));

}

void ASEA_Sword_First::BeginPlay()
{
	Super::BeginPlay();
	auto MyPlayer = Cast<AMyPlayer>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	OwnerPlayer = MyPlayer;

	FTimerDelegate TimeCallback;
	TimeCallback.BindLambda([this] {
		this->Destroy();
		GetWorldTimerManager().ClearTimer(DestroyTimerHandle);
		});
	GetWorldTimerManager().SetTimer(DestroyTimerHandle, TimeCallback, 1.5f, false);
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
