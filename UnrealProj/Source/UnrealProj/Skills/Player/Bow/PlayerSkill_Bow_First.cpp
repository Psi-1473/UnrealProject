// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerSkill_Bow_First.h"
#include "../../../Creatures/Player/MyPlayer.h"
#include "../../../Animations/Player/PlayerAnim.h"
#include "../../../DEFINE.h"
#include "../../../State/CharacterState.h"
#include "../../EffectActor/SkillRangeActor.h"

UPlayerSkill_Bow_First::UPlayerSkill_Bow_First()
{
	Id = 1;
	WeaponType = WEAPON_ARROW;
	bRange = true;
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
	RangeActor->MakeThisToCircle(1.5f);
	RangeActor->GetMesh()->SetCollisionProfileName("NoCollision");
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
}
