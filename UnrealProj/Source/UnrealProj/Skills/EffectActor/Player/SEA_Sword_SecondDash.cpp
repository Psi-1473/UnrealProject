// Fill out your copyright notice in the Description page of Project Settings.


#include "SEA_Sword_SecondDash.h"
#include "Components/CapsuleComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Engine/DamageEvents.h"
#include "../../../Creatures/Player/MyPlayer.h"
#include "../../../Creatures/Monster/Monster.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Engine/DamageEvents.h"


ASEA_Sword_SecondDash::ASEA_Sword_SecondDash()
{
	PrimaryActorTick.bCanEverTick = true;
	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> MA(TEXT("/Script/Niagara.NiagaraSystem'/Game/ParagonAurora/FX/Particles/Abilities/Dash/FX/P_Aurora_Dash_Flare_Converted.P_Aurora_Dash_Flare_Converted'"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> GA(TEXT("/Script/Engine.ParticleSystem'/Game/ParagonAurora/FX/Particles/Abilities/Leap/FX/P_Aurora_Decoy_Frost.P_Aurora_Decoy_Frost'"));

	if (MA.Succeeded())
		ParticleComponent->SetAsset(MA.Object);
	if (GA.Succeeded())
		GroundParticle = GA.Object;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CAPSULE"));
	CapsuleComponent->SetRelativeScale3D(FVector(3.f, 3.f, 3.f));
	CapsuleComponent->SetRelativeLocation(FVector(30.f, 0.f, 0.f));
	CapsuleComponent->SetRelativeRotation(FRotator(90.f, 0.f, 0.f));
	CapsuleComponent->SetCapsuleHalfHeight(70.f, false);
	CapsuleComponent->SetCapsuleRadius(40.f, false);
	CapsuleComponent->SetCollisionProfileName("Arrow");
	CapsuleComponent->OnComponentBeginOverlap.AddDynamic(this, &ASEA_Sword_SecondDash::OnOverlapBegin);

	CapsuleComponent->SetupAttachment(RootComponent);
}

void ASEA_Sword_SecondDash::BeginPlay()
{
	Super::BeginPlay();
}

void ASEA_Sword_SecondDash::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	auto OwnerPlayer = Cast<AMyPlayer>(Owner);
	SetActorLocation(OwnerPlayer->GetActorLocation());
	SetActorRotation(OwnerPlayer->GetActorRotation());
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), GroundParticle, GetActorLocation() - FVector(1.f, 1.f, 50.f));
}

void ASEA_Sword_SecondDash::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && (OtherActor != this))
	{
		auto Enemy = Cast<AMonster>(OtherActor);
		auto OwnerPlayer = Cast<AMyPlayer>(Owner);
		if (Enemy)
		{
			FDamageEvent DamageEvent;
			if (OwnerPlayer == nullptr)
			{
				UE_LOG(LogTemp, Warning, TEXT("OWNER NULL"));
				return;
			}
			Enemy->OnDamaged(10, DamageEvent, OwnerPlayer->GetController(), OwnerPlayer);
		}
	}
}
