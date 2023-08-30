// Fill out your copyright notice in the Description page of Project Settings.


#include "SevarogSkill_Sixth.h"
#include "../../../Creatures/Monster/BossMonster.h"
#include "../../../AI/BossAIController.h"
#include "../../../Animations/Monster/BossAnimInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"
#include "../../EffectActor/SkillEffectActor.h"

USevarogSkill_Sixth::USevarogSkill_Sixth()
{
	Id = 6;
	CoolTime = 25.f;
	static ConstructorHelpers::FClassFinder<ASkillEffectActor> EFFECT(TEXT("/Script/Engine.Blueprint'/Game/02_Blueprints/SkillEffectActor/Sevarog/BP_SevarogSixth.BP_SevarogSixth_C'"));

	if (EFFECT.Succeeded()) Effect = EFFECT.Class;
}

void USevarogSkill_Sixth::Execute(AActor* OwnerActor, bool bRangeAttack)
{
	// ĳ���� �ִϸ��̼� Ʋ��
	Super::Execute(OwnerActor, bRangeAttack);
	bCanUse = false;
	auto Boss = Cast<ABossMonster>(OwnerMonster);
	Boss->SetSixthSkill(true);
	Boss->SetExecutingSkill(this);
	OwnerMonster->GetWorldTimerManager().SetTimer(SpawnTickTimer, this, &USevarogSkill_Sixth::SpawnTornado, 1.f, true);
}

void USevarogSkill_Sixth::SpawnTornado()
{
	if (Count >= 5)
	{
		OwnerMonster->GetWorldTimerManager().ClearTimer(SpawnTickTimer);
		OwnerMonster->GetWorldTimerManager().SetTimer(SpawnTickTimer, this, &USevarogSkill_Sixth::DestroyTornado, 3.f, false);
		UE_LOG(LogTemp, Warning, TEXT("START END SKILL TIMER"));
	}
	else
	{
		Count++;
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = Cast<AActor>(OwnerMonster);
		SpawnParams.Instigator = OwnerMonster->GetInstigator();
		FVector SpawnLocation = OwnerMonster->GetActorLocation() - FVector(0.f, 0.f, 300.f);
		ASkillEffectActor* EActor = OwnerMonster->GetWorld()->SpawnActor<ASkillEffectActor>(Effect,
			SpawnLocation,
			OwnerMonster->GetActorRotation(),
			SpawnParams);

		ActorArray.Add(EActor);
		// ���� ����̵� ��ü ��ȯ
		// ��ȯ�ϰ� ������ �����ؼ� ����ֱ�
		UE_LOG(LogTemp, Warning, TEXT("SPAWN ! SIXTH"));
	}
}

void USevarogSkill_Sixth::DestroyTornado()
{
	// ������ ������ ���� Destroy�ϱ�
	for (int i = 0; i < ActorArray.Num(); i++)
	{
		bool a = ActorArray[i]->Destroy();//�� �ȵǳ�
		if (a == true)
		{
			UE_LOG(LogTemp, Warning, TEXT("DESTROY! "));
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("DESTROY FAILED!"));
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("END SKILL SIXTH"));
	Count = 0;
	ActorArray.Empty();
	auto Boss = Cast<ABossMonster>(OwnerMonster);
	Boss->SetSixthSkill(false);
	SkillEnd();
}

