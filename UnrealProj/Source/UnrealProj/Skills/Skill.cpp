// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill.h"
#include "EffectActor//SkillEffectActor.h"
#include "EffectActor//SkillRangeActor.h"
#include "../State/CharacterState.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Image.h"

USkill::USkill()
{
	static ConstructorHelpers::FClassFinder<ASkillRangeActor> RANGE(TEXT("/Script/Engine.Blueprint'/Game/02_Blueprints/SkillEffectActor/RangeActor.RangeActor_C'"));

	if (RANGE.Succeeded()) SkillRangeActor = RANGE.Class;
}

void USkill::Execute(AActor* OwnerActor, bool bRangeAttack)
{
	if (RemainingTime > 0.f)
		return;

	if (!bCanUse)
		return;
}

void USkill::SkillEnd()
{
	RemainingTime = (float)CoolDown;
}

void USkill::DestroyActor()
{
	if (EffectActor == nullptr)
		return;

	EffectActor->Destroy();
}



void USkill::PlaySoundAtLocation(UWorld* Wolrd, FVector Location, USoundBase* Sound)
{
	if (Sound == nullptr)
		return;
	UGameplayStatics::PlaySoundAtLocation(Wolrd, Sound, Location);
}




