// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerSkill_Bow_First.h"
#include "../../../Creatures/Player/MyPlayer.h"
#include "../../../Animations/Player/PlayerAnim.h"
#include "../../../DEFINE.h"
#include "../../../State/CharacterState.h"
#include "../../../State/StateMachine.h"
#include "../../EffectActor/SkillRangeActor.h"
#include "../../../CameraShakes/SkillHitCameraShake.h"
#include "Components/CapsuleComponent.h"
#include "../../EffectActor/SkillEffectActor.h"
#include "../../../Items/Weapons/Weapon.h"
#include "Engine/Texture2D.h"
#include "Components/Image.h"
#include "../../../MyGameInstance.h"



UPlayerSkill_Bow_First::UPlayerSkill_Bow_First()
{
	bRange = true;

	static ConstructorHelpers::FClassFinder<ASkillEffectActor> EFFECT(TEXT("/Script/Engine.Blueprint'/Game/02_Blueprints/SkillEffectActor/Player/1/BP_Effect_1_1.BP_Effect_1_1_C'"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> IMG(TEXT("/Script/Engine.Texture2D'/Game/09_Image/Skill/Arrow2.Arrow2'"));
	static ConstructorHelpers::FClassFinder<USkillHitCameraShake> SHAKE(TEXT("/Script/Engine.Blueprint'/Game/02_Blueprints/CameraShakes/Player/Skill/Bow/BP_Shake_Bow1.BP_Shake_Bow1_C'"));

	if (EFFECT.Succeeded()) Effect = EFFECT.Class;
	if (IMG.Succeeded())Txt = IMG.Object;
	if (SHAKE.Succeeded()) CameraShake = SHAKE.Class;
}

void UPlayerSkill_Bow_First::Execute(AActor* OwnerActor, bool bRangeAttack)
{
	// 부모 함수에서 return 해봤자 Super::Execute만 종료되고 
	// 그 아래 다른 함수들은 실행되기 때문에 이거 조심
	Super::Execute(OwnerActor, bRangeAttack);
	STATE MyState = OwnerPlayer->GetStateMachine()->GetState()->GetState();
	if (RemainingTime > 0.f)
		return;
	if (MyState == STATE::ATTACK)
		return;

	OwnerPlayer->SetSkill(this);
	OwnerPlayer->GetAnimInst()->SetBowCast(true);
	OwnerPlayer->GetStateMachine()->SetState(STATE::SKILLCAST);

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = Cast<AActor>(OwnerPlayer);
	SpawnParams.Instigator = OwnerPlayer->GetInstigator();

	FRotator SpawnRot = OwnerPlayer->GetActorRotation();
	FVector SpawnPos = OwnerPlayer->GetActorLocation();// *FVector(1.f, 1.f, .f);
	
	RangeActor = OwnerPlayer->GetWorld()->SpawnActor<ASkillRangeActor>(SkillRangeActor, SpawnPos, SpawnRot, SpawnParams);
	RangeActor->SetRange(Cast<AActor>(OwnerPlayer), 2);
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
	OwnerPlayer->GetAnimInst()->SetBowCast(false);
	SetDefaultValue();

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = Cast<AActor>(OwnerPlayer);
	SpawnParams.Instigator = OwnerPlayer->GetInstigator();

	FRotator SpawnRot = OwnerPlayer->GetActorRotation();
	FVector SpawnPos = OwnerPlayer->GetSpawnedRangeActor()->GetActorLocation();
	OwnerPlayer->GetSpawnedRangeActor()->Destroy();
	OwnerPlayer->SetRangeActor(nullptr);
	EffectActor = OwnerPlayer->GetWorld()->SpawnActor<ASkillEffectActor>(Effect, SpawnPos, SpawnRot, SpawnParams);
	EffectActor->SetOwner(Cast<AActor>(OwnerPlayer));
	OwnerPlayer->ShakeCamera(CameraShake);
}
