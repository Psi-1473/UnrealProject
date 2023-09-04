// Fill out your copyright notice in the Description page of Project Settings.


#include "SevarogSkill_Fifth.h"
#include "../../../Creatures/Monster/BossMonster.h"
#include "../../../Animations/Monster/BossAnimInstance.h"
#include "../../../Projectiles/Projectile.h"


USevarogSkill_Fifth::USevarogSkill_Fifth()
{
	Id = 5;
	CoolTime = 5.f;
	static ConstructorHelpers::FClassFinder<AProjectile> PROJ(TEXT("/Script/Engine.Blueprint'/Game/02_Blueprints/Projectiles/BP_SevarogFireball.BP_SevarogFireball_C'"));

	if (PROJ.Succeeded()) FireProjectile = PROJ.Class;
	
}

void USevarogSkill_Fifth::Execute(AActor* OwnerActor, bool bRangeAttack)
{
	// 불 날리는 (무기 휘두르는) 애니메이션 실행
	Super::Execute(OwnerActor, bRangeAttack);
	bCanUse = false;
	auto Boss = Cast<ABossMonster>(OwnerMonster);
	Boss->GetAnimInst()->PlaySkillMontage(Id);
	Boss->SetExecutingSkill(this);
	AttackOrSpawnSkillActor();
}

void USevarogSkill_Fifth::AttackOrSpawnSkillActor()
{
	// Projectile 소환
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = Cast<AActor>(OwnerMonster);
	SpawnParams.Instigator = OwnerMonster->GetInstigator();

	AProjectile* Projectile = OwnerMonster->GetWorld()->SpawnActor<AProjectile>(FireProjectile,
		OwnerMonster->GetActorLocation() + OwnerMonster->GetActorUpVector() * -75.f,
		OwnerMonster->GetActorRotation(),
		SpawnParams);

	Projectile->FireInDirection(Projectile->GetActorForwardVector(), 1.f);
}
