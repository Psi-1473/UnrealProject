// Fill out your copyright notice in the Description page of Project Settings.


#include "BossMonster.h"
#include "../../AI/BossAIController.h"
#include "../Player/MyPlayer.h"
#include "Kismet/GameplayStatics.h"
#include "../../Animations/Monster/BossAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "../../Skills/Monster/Sevarog/SevarogSkill_First.h"
#include "../../Skills/Monster/Sevarog/SevarogSkill_Second.h"
#include "../../Skills/Monster/Sevarog/SevarogSkill_Third.h"
#include "../../Skills/Monster/Sevarog/SevarogSkill_Fourth.h"
#include "../../Skills/Monster/Sevarog/SevarogSkill_Fifth.h"
#include "../../Skills/Monster/Sevarog/SevarogSkill_Sixth.h"
#include "../../Skills/EffectActor/SkillRangeActor.h"

ABossMonster::ABossMonster()
{
	AIControllerClass = ABossAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	auto Movement = Cast<UCharacterMovementComponent>(GetMovementComponent());
	Movement->MaxWalkSpeed = 300.f;
}

void ABossMonster::BeginPlay()
{
	Super::BeginPlay();
	auto Char = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	auto MyPlayer = Cast<AMyPlayer>(Char);
	TargetPlayer = MyPlayer;
	GetWorldTimerManager().SetTimer(SkillCoolTimer, this, &ABossMonster::SetCanSkillTrue, 10.f, true);
	GetWorldTimerManager().SetTimer(DashCoolTimer, this, &ABossMonster::SetCanDashTrue, 5.f, true);

	auto AIController = Cast<ABossAIController>(GetController());
	AIController->SetTarget(TargetPlayer);

	USevarogSkill_First* NewSkill = NewObject<USevarogSkill_First>();
	NewSkill->SetOwnerMonster(this);
	SkillList.Add(NewSkill);
	USevarogSkill_Second* NewSkill2 = NewObject<USevarogSkill_Second>();
	NewSkill2->SetOwnerMonster(this);
	SkillList.Add(NewSkill2);
	USevarogSkill_Third* NewSkill3 = NewObject<USevarogSkill_Third>();
	NewSkill3->SetOwnerMonster(this);
	SkillList.Add(NewSkill3);
	USevarogSkill_Fourth* NewSkill4 = NewObject<USevarogSkill_Fourth>();
	NewSkill4->SetOwnerMonster(this);
	SkillList.Add(NewSkill4);
	USevarogSkill_Fifth* NewSkill5 = NewObject<USevarogSkill_Fifth>();
	NewSkill5->SetOwnerMonster(this);
	SkillList.Add(NewSkill5);
	USevarogSkill_Sixth* NewSkill6 = NewObject<USevarogSkill_Sixth>();
	NewSkill6->SetOwnerMonster(this);
	SkillList.Add(NewSkill6);

	UE_LOG(LogTemp, Warning, TEXT("Boss : Skill Size : %d"), SkillList.Num());
}

void ABossMonster::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	AnimInst = Cast<UBossAnimInstance>(GetMesh()->GetAnimInstance());
	//AnimInst->OnDied.AddUObject(this, &ABossMonster::DestroyObject);
}

void ABossMonster::UseSkill()
{
	if (bCanSkill == false)
		return;

	if (SkillList.Num() <= 0)
		return;

	UMonsterSkill* Skill = SelectSkill();
	if (Skill == nullptr)
		return;

	bCanSkill = false;
	Skill->Execute(this, false);
	//SkillList[0]->Execute(this, false); Test 용


}

UMonsterSkill* ABossMonster::SelectSkill()
{
	TArray<UMonsterSkill*> Arr;
	for (int i = 0; i < SkillList.Num(); i++)
	{
		if (SkillList[i]->GetCanUse())
			Arr.Add(SkillList[i]);
	}

	int SkillNumber = Arr.Num();

	if (SkillNumber <= 0)
		return nullptr;

	int Index = FMath::RandRange(0, SkillNumber - 1);
	return Arr[Index];
}

void ABossMonster::Dash()
{
	// 테스트용 함수
	UE_LOG(LogTemp, Warning, TEXT("Boss : Dash !"));

	bCanDash = false;
	GetWorldTimerManager().SetTimer(DashCoolTimer, this, &ABossMonster::SetCanDashTrue, 5.f, true);
	
	//if(거리 체크, 멀면 대쉬)
}

void ABossMonster::StartCooldown()
{
	GetWorldTimerManager().SetTimer(SkillCoolTimer, this, &ABossMonster::SetCanSkillTrue, 7.f, true);
}


void ABossMonster::AttackTarget()
{
	AnimInst->PlayAttackMontage();
	//RangeCount++;
	//if (RangeCount == 3)
	//{
	//	RangeCount = 0;

		//	return;
		//}
		//FActorSpawnParameters SpawnParams;
		//SpawnParams.Owner = this;
		//SpawnParams.Instigator = GetInstigator();
		//
		//FRotator SpawnRot = GetActorRotation();
		//FVector SpawnPos = GetActorLocation() * FVector(1.f, 1.f, 0.f);
		//
		//ASkillRangeActor* RangeActor = GetWorld()->SpawnActor<ASkillRangeActor>(ASkillRangeActor::StaticClass(), SpawnPos, SpawnRot, SpawnParams);
		//RangeActor->SetRange(this, 2, 90.f, 0.2f);
		//
		//GetWorldTimerManager().SetTimer(RangeToAttackTimer, this, &ABossMonster::AttackTarget, 0.5f, false);
}

float ABossMonster::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	// 부모 상속받을지 결정
	PopupDamageText(Damage);
	return Damage;
}

void ABossMonster::Die(AMyPlayer* Player)
{
}

void ABossMonster::DestroyObject()
{
}

void ABossMonster::SetCanSkillTrue()
{
	auto AIController = Cast<ABossAIController>(GetController());
	AIController->StopAI();
	AIController->StartAI();
	bCanSkill = true;
}

void ABossMonster::SetCanDashTrue()
{
	bCanDash = true;
}
