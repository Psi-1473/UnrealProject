// Fill out your copyright notice in the Description page of Project Settings.


#include "SEA_Sevarog_Sixth.h"
#include "Components/CapsuleComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Engine/DamageEvents.h"
#include "../../../Creatures/Player/MyPlayer.h"
#include "Kismet/GameplayStatics.h"

ASEA_Sevarog_Sixth::ASEA_Sevarog_Sixth()
{
	PrimaryActorTick.bCanEverTick = true;
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CAPSULE"));

	static ConstructorHelpers::FObjectFinder<UParticleSystem> PA(TEXT("/Script/Engine.ParticleSystem'/Game/FXVarietyPack/Particles/P_ky_storm.P_ky_storm'"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> HITEFFECT(TEXT("/Script/Engine.ParticleSystem'/Game/FXVarietyPack/Particles/P_ky_hit1.P_ky_hit1'"));

	if (PA.Succeeded()) LegacyParticleComponent->SetTemplate(PA.Object);
	if (HITEFFECT.Succeeded()) HitParticle = HITEFFECT.Object;

	CapsuleComponent->SetRelativeScale3D(FVector(8.0f, 4.0f, 5.0f));
	CapsuleComponent->OnComponentBeginOverlap.AddDynamic(this, &ASEA_Sevarog_Sixth::OnOverlapBegin);
	CapsuleComponent->OnComponentEndOverlap.AddDynamic(this, &ASEA_Sevarog_Sixth::OnOverlapEnd);
	CapsuleComponent->SetupAttachment(RootComponent);
}

void ASEA_Sevarog_Sixth::BeginPlay()
{
	Super::BeginPlay();
}

void ASEA_Sevarog_Sixth::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto Char = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	auto Player = Cast<AMyPlayer>(Char);
	FVector TargetPos = Player->GetActorLocation();
	FVector MoveDir = TargetPos - GetActorLocation();
	
	SetActorLocation(GetActorLocation() + MoveDir.GetSafeNormal() * 5.f);
}

void ASEA_Sevarog_Sixth::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && (OtherActor != this))
	{
		auto Player = Cast<AMyPlayer>(OtherActor);
		if (Player)
		{
			TargetPlayer = Player;
			UE_LOG(LogTemp, Warning, TEXT("Sevarog Sixth Skill Hit Player"));
			FDamageEvent DamageEvent;
			TargetPlayer->OnDamaged(1, DamageEvent, Owner->GetInstigatorController(), Owner);
			Owner->GetWorldTimerManager().SetTimer(HitTickTimer, this, &ASEA_Sevarog_Sixth::HitPlayer, 0.5f, true);
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitParticle, TargetPlayer->GetActorLocation());
		}
	}
}

void ASEA_Sevarog_Sixth::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && (OtherActor != this))
	{
		auto Player = Cast<AMyPlayer>(OtherActor);
		if (Player)
		{
			TargetPlayer = nullptr;
			UE_LOG(LogTemp, Warning, TEXT("Sevarog Sixth Skill Out Player"));
			Owner->GetWorldTimerManager().ClearTimer(HitTickTimer);
		}
	}
}

void ASEA_Sevarog_Sixth::HitPlayer() {

	if (TargetPlayer == nullptr)
		return;
	UE_LOG(LogTemp, Warning, TEXT("Sevarog Sixth Skill Hit Player"));
	FDamageEvent DamageEvent;
	TargetPlayer->OnDamaged(1, DamageEvent, Owner->GetInstigatorController(), Owner);
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitParticle, TargetPlayer->GetActorLocation());
}
