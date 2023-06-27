// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerSkill_Bow_First.h"
#include "../../../Creatures/Player/MyPlayer.h"
#include "../../../Animations/Player/PlayerAnim.h"
#include "../../../DEFINE.h"
#include "../../../State/CharacterState.h"
#include "../../EffectActor/SkillRangeActor.h"
#include "Components/CapsuleComponent.h"
#include "../../EffectActor/SkillEffectActor.h"

UPlayerSkill_Bow_First::UPlayerSkill_Bow_First()
{
	Id = 1;
	WeaponType = WEAPON_ARROW;
	bRange = true;

	static ConstructorHelpers::FClassFinder<ASkillEffectActor> EFFECT(TEXT("/Script/Engine.Blueprint'/Game/02_Blueprints/SkillEffectActor/Player/1/BP_Effect_1_1.BP_Effect_1_1_C'"));

	if (EFFECT.Succeeded())
		Effect = EFFECT.Class;



}

void UPlayerSkill_Bow_First::Execute(AActor* OwnerActor, bool bRangeAttack)
{
	Super::Execute(OwnerActor, bRangeAttack);

	if (OwnerPlayer->GetState() == OwnerPlayer->GetSpecificState(STATE::ATTACK))
		return;

	OwnerPlayer->SetSkill(this);
	OwnerPlayer->GetAnimInst()->SetBowCast(true);
	OwnerPlayer->SetState(STATE::SKILLCAST);

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = OwnerPlayer;
	SpawnParams.Instigator = OwnerPlayer->GetInstigator();

	FRotator SpawnRot = OwnerPlayer->GetActorRotation();
	FVector SpawnPos = OwnerPlayer->GetActorLocation() * FVector(1.f, 1.f, 0.f);
	
	RangeActor = OwnerPlayer->GetWorld()->SpawnActor<ASkillRangeActor>(ASkillRangeActor::StaticClass(), SpawnPos, SpawnRot, SpawnParams);
	RangeActor->MakeThisToCircle(2.2f);
	RangeActor->GetMesh()->SetCollisionProfileName("NoCollision");
	//RangeActor->GetMesh()->SetMaterial(0, )
	OwnerPlayer->SetRangeActor(RangeActor);

}

void UPlayerSkill_Bow_First::PlayParticle(AActor* OwnerActor)
{
}

void UPlayerSkill_Bow_First::DestroyActor()
{
}

void UPlayerSkill_Bow_First::CastToExecute(AActor* OwnerActor)
{
	Super::CastToExecute(OwnerActor);
	OwnerPlayer->SetState(STATE::SKILL);
	OwnerPlayer->SetSkill(this);
	OwnerPlayer->GetAnimInst()->SetBowCast(false);
	OwnerPlayer->GetAnimInst()->PlaySkillMontage(Id);

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = OwnerPlayer; 
	SpawnParams.Instigator = OwnerPlayer->GetInstigator();

	FRotator SpawnRot = OwnerPlayer->GetSpawnedRangeActor()->GetActorRotation();
	FVector SpawnPos = OwnerPlayer->GetSpawnedRangeActor()->GetActorLocation();
	OwnerPlayer->GetSpawnedRangeActor()->Destroy();
	OwnerPlayer->SetRangeActor(nullptr);
	EffectActor = OwnerPlayer->GetWorld()->SpawnActor<ASkillEffectActor>(Effect, SpawnPos, SpawnRot, SpawnParams);
}
