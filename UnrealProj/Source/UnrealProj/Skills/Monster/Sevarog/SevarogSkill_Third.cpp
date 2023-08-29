// Fill out your copyright notice in the Description page of Project Settings.


#include "SevarogSkill_Third.h"
#include "../../../Creatures/Monster/BossMonster.h"
#include "../../../Creatures/Player/MyPlayer.h"
#include "../../../Animations/Monster/BossAnimInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"
#include "../../../Projectiles/Projectile.h"

USevarogSkill_Third::USevarogSkill_Third()
{
	Id = 3;
	CoolTime = 20.f;
	static ConstructorHelpers::FClassFinder<AProjectile> PROJ(TEXT("/Script/Engine.Blueprint'/Game/02_Blueprints/Projectiles/BP_SevarogFire.BP_SevarogFire_C'"));

	if (PROJ.Succeeded())
		FireProjectile = PROJ.Class;
}

void USevarogSkill_Third::Execute(AActor* OwnerActor, bool bRangeAttack)
{
	// 전조 이펙트 틀고 1.5초 뒤 발사
	Super::Execute(OwnerActor, bRangeAttack);
	bCanUse = false;
	auto Boss = Cast<ABossMonster>(OwnerMonster);
	Boss->SetExecutingSkill(this);
	OwnerMonster->GetWorldTimerManager().SetTimer(FireTimerHandle, this, &USevarogSkill_Third::PlaySkillEffect, 0.5f, false);
}

void USevarogSkill_Third::PlaySkillEffect()
{
	auto Boss = Cast<ABossMonster>(OwnerMonster);
	Boss->GetAnimInst()->PlaySkillMontage(Id);
}

void USevarogSkill_Third::Attack()
{
	// 발사

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = Cast<AActor>(OwnerMonster);
	SpawnParams.Instigator = OwnerMonster->GetInstigator();

	AProjectile* Projectile = OwnerMonster->GetWorld()->SpawnActor<AProjectile>(FireProjectile,
		OwnerMonster->GetActorLocation() + OwnerMonster->GetActorUpVector() * 55.f,
		OwnerMonster->GetActorRotation(),
		SpawnParams);

		Projectile->FireInDirection(Projectile->GetActorForwardVector(), 1.f);

		OwnerMonster->GetWorldTimerManager().SetTimer(CoolTimeHandler, this, &UMonsterSkill::EndCoolDown, CoolTime, false);

}

void USevarogSkill_Third::PlaySwingAnim()
{
}
