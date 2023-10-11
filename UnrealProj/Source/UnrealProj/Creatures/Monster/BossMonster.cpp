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
#include "../../Stat/MonsterStatComponent.h"
#include "../../Managers/UIManager.h"
#include "../../Managers/SoundManager.h"
#include "../../MyGameInstance.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine/LatentActionManager.h"
#include "Particles/ParticleSystemComponent.h"
#include "Sound/SoundWave.h"

ABossMonster::ABossMonster()
{
	AIControllerClass = ABossAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	auto Movement = Cast<UCharacterMovementComponent>(GetMovementComponent());
	Movement->MaxWalkSpeed = 300.f;
	DashParticleComp = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("DashEffect"));
	DashParticleComp->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UParticleSystem> DASH(TEXT("/Script/Engine.ParticleSystem'/Game/ParagonSevarog/FX/Particles/Abilities/SoulStackPassive/FX/P_ShadowTrailsCharSelect.P_ShadowTrailsCharSelect'"));
	static ConstructorHelpers::FObjectFinder<USoundWave> BGM(TEXT("/Script/Engine.SoundWave'/Game/10_Sound/BGM/BGM_Boss.BGM_Boss'"));
	if (DASH.Succeeded()) DashParticleComp->SetTemplate(DASH.Object);
	if (BGM.Succeeded()) BossBgm = BGM.Object;
}

void ABossMonster::BeginPlay()
{
	Super::BeginPlay();
	AnimInst->PlayStartMontage();
	auto Char = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	auto MyPlayer = Cast<AMyPlayer>(Char);
	SetActorRotation(FRotator(0.f, -150.f, 0.f));
	TargetPlayer = MyPlayer;
	GetWorldTimerManager().SetTimer(SkillCoolTimer, this, &ABossMonster::SetCanSkillTrue, 17.f, false);
	GetWorldTimerManager().SetTimer(DashCoolTimer, this, &ABossMonster::SetCanDashTrue, 12.f, false);
	
	auto AIController = Cast<ABossAIController>(GetController());
	AIController->SetTarget(TargetPlayer);
	AIController->StopAI();
	SetDashEffectVisibility(false);

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

	auto GInstance = Cast<UMyGameInstance>(GetGameInstance());
	GInstance->GetSoundMgr()->SetBGM(BossBgm);
	
}

void ABossMonster::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	AnimInst = Cast<UBossAnimInstance>(GetMesh()->GetAnimInstance());
	//AnimInst->OnDied.AddUObject(this, &ABossMonster::DestroyObject);
}

void ABossMonster::SetDashEffectVisibility(bool Value)
{
	DashParticleComp->SetVisibility(Value);
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
	FVector TargetLoc = TargetPlayer->GetActorLocation();
	TargetLoc.Z = GetActorLocation().Z;
	FRotator Rot = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), TargetLoc);
	SetActorRotation(Rot);
	Skill->Execute(this, false);
	//SkillList[2]->Execute(this, false);


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
	AnimInst->Dash();
	FLatentActionInfo ActInfo;
	ActInfo.CallbackTarget = this;
	FVector TargetLoc = TargetPlayer->GetActorLocation();
	TargetLoc.Z = GetActorLocation().Z;
	FRotator Rot = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), TargetPlayer->GetActorLocation());
	SetActorRotation(Rot);
	SetDashEffectVisibility(true);
	UKismetSystemLibrary::MoveComponentTo(
		RootComponent,
		TargetLoc,
		Rot,
		true,
		true,
		1.5f,
		true,
		EMoveComponentAction::Move,
		ActInfo
		);
	GetWorldTimerManager().SetTimer(DashCoolTimer, this, &ABossMonster::SetCanDashTrue, 5.f, false);
	
	//if(거리 체크, 멀면 대쉬)
}

void ABossMonster::StartCooldown()
{
	GetWorldTimerManager().SetTimer(SkillCoolTimer, this, &ABossMonster::SetCanSkillTrue, 7.f, false);
}


void ABossMonster::AttackTarget(AMyPlayer* Target)
{
	FVector TargetLoc = TargetPlayer->GetActorLocation();
	TargetLoc.Z = GetActorLocation().Z;
	FRotator Rot = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), TargetLoc);

	SetActorRotation(Rot);
	AnimInst->PlayAttackMontage();
	
}

void ABossMonster::OnDamaged(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser, UParticleSystem* Particle, AttackType Type)
{
	// 1. Damage Type에 따라 처리
	if (Particle != nullptr)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Particle, GetActorLocation());
	}
	TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
}


float ABossMonster::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	// 부모 상속받을지 결정

	PopupDamageText(Damage);
	StatComponent->SetHp(StatComponent->GetHp() - Damage);

	if (StatComponent->GetHp() <= 0)
		Die(TargetPlayer);

	return Damage;
}

void ABossMonster::Die(AMyPlayer* Player)
{
	if (bDie)
		return;
	bDie = true;
	auto AIController = Cast<ABossAIController>(GetController());

	GetWorldTimerManager().ClearTimer(SkillCoolTimer);
	GetWorldTimerManager().ClearTimer(DashCoolTimer);

	if(ExecutingSkill != nullptr)
		ExecutingSkill->SkillEnd();

	AIController->StopAI();
	AnimInst->PlayDieMontage();
	auto GInstance = Cast<UMyGameInstance>(GetGameInstance());
	GInstance->GetUIMgr()->CloseUI((int)UIType::BossHpBar);
	GInstance->CheckQuest(QUEST_HUNT, StatComponent->GetId(), Player);
	GInstance->GetSoundMgr()->PlayAreaBgm();
}

void ABossMonster::DestroyObject()
{
	SetActorHiddenInGame(true);
	Destroy();
}

void ABossMonster::SetCanSkillTrue()
{
	UE_LOG(LogTemp, Warning, TEXT("Boss can use skills."));
	auto AIController = Cast<ABossAIController>(GetController());
	AIController->StopAI();
	AIController->StartAI();
	bCanSkill = true;
}

void ABossMonster::SetCanDashTrue()
{
	bCanDash = true;
}
