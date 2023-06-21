// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerSkill_Sword_Second.h"
#include "../../../Creatures/Player/MyPlayer.h"
#include "../../../Animations/Player/PlayerAnim.h"
#include "../../EffectActor/SkillEffectActor.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "../../EffectActor/Player/SEA_Sword_SecondDash.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

UPlayerSkill_Sword_Second::UPlayerSkill_Sword_Second()
{
	Id = 2;

	static ConstructorHelpers::FClassFinder<ASkillEffectActor> EFFECT(TEXT("/Script/Engine.Blueprint'/Game/02_Blueprints/SkillEffectActor/Player/0/BP_Effect_0_2_Dash.BP_Effect_0_2_Dash_C'"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> PP(TEXT("/Script/Engine.ParticleSystem'/Game/ParagonAurora/FX/Particles/Abilities/Leap/FX/P_Aurora_Decoy_Spawn.P_Aurora_Decoy_Spawn'"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> DP(TEXT("/Script/Engine.ParticleSystem'/Game/ParagonAurora/FX/Particles/Abilities/Leap/FX/P_Aurora_Decoy_Explode_Fragments.P_Aurora_Decoy_Explode_Fragments'"));
	
	if (EFFECT.Succeeded())
		Effect = EFFECT.Class;
	if (PP.Succeeded())
		PlayerParticle = PP.Object;
	if (DP.Succeeded())
		DestroyParticle = DP.Object;
}

void UPlayerSkill_Sword_Second::Execute(AActor* OwnerActor)
{
	Super::Execute(OwnerActor);
	auto Player = Cast<AMyPlayer>(OwnerActor);
	MoveDir = OwnerActor->GetActorForwardVector();
	Player->GetCharacterMovement()->SetMovementMode(MOVE_Flying);
	Player->bUseControllerRotationYaw = false;
	OwnerPlayer->SetSkill(this);
	OwnerPlayer->GetAnimInst()->PlaySkillMontage(Id);
	UGameplayStatics::SpawnEmitterAtLocation(OwnerPlayer->GetWorld(), PlayerParticle, OwnerPlayer->GetActorLocation());
}

void UPlayerSkill_Sword_Second::PlayParticle(AActor* OwnerActor)
{
	Super::PlayParticle(OwnerActor);

	if (Effect == nullptr)
		return;
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = OwnerPlayer;
	SpawnParams.Instigator = OwnerPlayer->GetInstigator();

	FRotator SpawnRot = OwnerPlayer->GetActorRotation();
	FVector SpawnPos = OwnerPlayer->GetActorLocation();

	EffectActor = OwnerPlayer->GetWorld()->SpawnActor<ASkillEffectActor>(Effect, SpawnPos, SpawnRot, SpawnParams);
}

void UPlayerSkill_Sword_Second::DestroyActor()
{
	Super::DestroyActor();
	UGameplayStatics::SpawnEmitterAtLocation(OwnerPlayer->GetWorld(), DestroyParticle, OwnerPlayer->GetActorLocation());
}
