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
	static ConstructorHelpers::FClassFinder<ASkillEffectActor> EFFECT(TEXT("/Script/Engine.Blueprint'/Game/02_Blueprints/SkillEffectActor/Sevarog/BP_SevarogSixth.BP_SevarogSixth_C'"));

	if (EFFECT.Succeeded()) Effect = EFFECT.Class;
}

void USevarogSkill_Sixth::BeginPlay()
{
	
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

void USevarogSkill_Sixth::PlaySkillEffect()
{

}

void USevarogSkill_Sixth::SpawnTornado()
{
	if (Count >= 5)
	{
		OwnerMonster->GetWorldTimerManager().ClearTimer(SpawnTickTimer);
		OwnerMonster->GetWorldTimerManager().SetTimer(SpawnTickTimer, this, &USevarogSkill_Sixth::EndSkill, 3.f, false);
		UE_LOG(LogTemp, Warning, TEXT("START END SKILL TIMER"));
	}
	else
	{
		Count++;
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = Cast<AActor>(OwnerMonster);
		SpawnParams.Instigator = OwnerMonster->GetInstigator();
		FVector SpawnLocation = OwnerMonster->GetActorLocation();
		SpawnLocation.Z = 0;
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

void USevarogSkill_Sixth::EndSkill()
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
	Boss->SetExecutingSkill(nullptr);
	auto AIController = Cast<ABossAIController>(Boss->GetController());
	AIController->StartAI();
	OwnerMonster->GetWorldTimerManager().ClearTimer(SpawnTickTimer);
	//	OwnerMonster->GetWorldTimerManager().SetTimer(CoolTimeHandler, this, &UMonsterSkill::EndCoolDown, CoolTime, false);
}
