// Fill out your copyright notice in the Description page of Project Settings.


#include "SEA_Bow_First.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Engine/DamageEvents.h"
#include "../../../Creatures/Monster/Monster.h"
#include "../../../Creatures/Player/MyPlayer.h"

ASEA_Bow_First::ASEA_Bow_First()
{
	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> PA(TEXT("/Script/Niagara.NiagaraSystem'/Game/ParagonSparrow/FX/Particles/Sparrow/Skins/Rogue/P_RainofArrows_Converted.P_RainofArrows_Converted'"));
	if (PA.Succeeded())
		ParticleComponent->SetAsset(PA.Object);

}

void ASEA_Bow_First::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(AttackDelayTimerHandle, this, &ASEA_Bow_First::AttackCheck, 0.5f, false);
}



void ASEA_Bow_First::AttackCheck()
{
	if (AttackCount < 5)
	{
		TArray<FHitResult> HitResults;

		FCollisionQueryParams Params(NAME_None, false, this);

		float Radius = 250.f;

		FVector StartVector = GetActorLocation();
		FVector EndVector = GetActorLocation() + GetActorForwardVector() * Radius;


		bool bResult = GetWorld()->SweepMultiByChannel(
			OUT HitResults, 
			StartVector,
			EndVector,
			FQuat::Identity,
			ECollisionChannel::ECC_GameTraceChannel5,
			FCollisionShape::MakeSphere(Radius),//측면, 높이, 정면
			Params);

		FVector Center = GetActorLocation();
		FColor DrawColor;
		if (bResult)
			DrawColor = FColor::Green;
		else
			DrawColor = FColor::Red;

		DrawDebugSphere(GetWorld(), Center, Radius, 32, DrawColor, false, 1.f);

		if (bResult && !HitResults.IsEmpty())
		{
			for (FHitResult HitResult : HitResults)
			{
				UE_LOG(LogTemp, Log, TEXT("Hit Actor : %s"), *HitResult.GetActor()->GetName());
				AMonster* Enemy = Cast<AMonster>(HitResult.GetActor());
				FDamageEvent DamageEvent;
				if (Enemy != nullptr)
					Enemy->TakeDamage(15.f, DamageEvent, OwnerPlayer->GetController(), this); //Temp
			}
		}

		GetWorldTimerManager().SetTimer(AttackDelayTimerHandle, this, &ASEA_Bow_First::AttackCheck, 0.5f, false);
		AttackCount++;
	}
	else
	{
		GetWorldTimerManager().ClearTimer(AttackDelayTimerHandle);
		Destroy();
	}
}
