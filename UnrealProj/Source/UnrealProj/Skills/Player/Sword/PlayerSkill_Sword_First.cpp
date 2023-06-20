// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerSkill_Sword_First.h"
#include "../../../Creatures/Player/MyPlayer.h"
#include "../../../Animations/Player/PlayerAnim.h"
#include "../../EffectActor/SkillEffectActor.h"

UPlayerSkill_Sword_First::UPlayerSkill_Sword_First()
{
	static ConstructorHelpers::FClassFinder<ASkillEffectActor> EFFECT(TEXT("/Script/Engine.Blueprint'/Game/02_Blueprints/SkillEffectActor/Player/0/BP_Effect_0_1.BP_Effect_0_1_C'"));

	if (EFFECT.Succeeded())
		Effect = EFFECT.Class;
}

void UPlayerSkill_Sword_First::Execute(AActor* OwnerActor)
{
	Super::Execute(OwnerActor);
	UE_LOG(LogTemp, Warning, TEXT("SWORD FIRST SKILL"));
	OwnerPlayer = Cast<AMyPlayer>(OwnerActor);

	if (OwnerPlayer == nullptr)
		return;
	OwnerPlayer->SetSkill(this);
	OwnerPlayer->GetAnimInst()->PlaySkillMontage(Id);


}

void UPlayerSkill_Sword_First::PlayParticle(AActor* OwnerActor)
{
	Super::PlayParticle(OwnerActor);
	

	if (Effect == nullptr)
		return;
	SetParticleTimer();
	
}

void UPlayerSkill_Sword_First::SetParticleTimer()
{
	if (SpawnCount < MaxSpawnCount)
	{
		if (OwnerPlayer == nullptr)
			return;

		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = OwnerPlayer;
		SpawnParams.Instigator = OwnerPlayer->GetInstigator();

		FRotator SpawnRot = OwnerPlayer->GetActorRotation() + FRotator(0.f, RotZ[SpawnCount], 0.f);
		FVector SpawnPos = OwnerPlayer->GetActorLocation() * FVector(1.f, 1.f, 0.f);
		SpawnPos += OwnerPlayer->GetActorForwardVector() * LocX[SpawnCount];
		SpawnPos += OwnerPlayer->GetActorRightVector() * LocY[SpawnCount];
		OwnerPlayer->GetWorld()->SpawnActor<ASkillEffectActor>(Effect, SpawnPos, SpawnRot, SpawnParams);
		SpawnCount++;
		OwnerPlayer->GetWorldTimerManager().SetTimer(SpawnTimerHandle, this, &UPlayerSkill_Sword_First::SetParticleTimer, 0.05f, true);
	}
	else
	{
		SpawnCount = 0;
		OwnerPlayer->GetWorldTimerManager().ClearTimer(SpawnTimerHandle);
	}
}

