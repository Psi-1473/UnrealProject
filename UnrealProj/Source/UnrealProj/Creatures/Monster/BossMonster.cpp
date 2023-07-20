// Fill out your copyright notice in the Description page of Project Settings.


#include "BossMonster.h"
#include "../../AI/BossAIController.h"
#include "../Player/MyPlayer.h"
#include "Kismet/GameplayStatics.h"
#include "../../Animations/Monster/BossAnimInstance.h"

ABossMonster::ABossMonster()
{
	AIControllerClass = ABossAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

void ABossMonster::BeginPlay()
{
	Super::BeginPlay();

	auto Char = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	auto MyPlayer = Cast<AMyPlayer>(Char);
	TargetPlayer = MyPlayer;

	auto AIController = Cast<ABossAIController>(GetController());
	AIController->SetTarget(TargetPlayer);

}

void ABossMonster::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	AnimInst = Cast<UBossAnimInstance>(GetMesh()->GetAnimInstance());
	//AnimInst->OnDied.AddUObject(this, &ABossMonster::DestroyObject);
}

void ABossMonster::UseSkill()
{
	// 테스트용 함수
	UE_LOG(LogTemp, Warning, TEXT("Boss : Use Skill !"));
	bCanSkill = false;
	GetWorldTimerManager().SetTimer(SkillCoolTimer, this, &ABossMonster::SetCanSkillTrue, 10.f, true);

}

void ABossMonster::Dash()
{
	// 테스트용 함수
	UE_LOG(LogTemp, Warning, TEXT("Boss : Dash !"));
	bCanDash = false;
	GetWorldTimerManager().SetTimer(DashCoolTimer, this, &ABossMonster::SetCanDashTrue, 5.f, true);
}

void ABossMonster::AttackTarget(AMyPlayer* Target)
{
	AnimInst->PlayAttackMontage();
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
	bCanSkill = true;
	auto AIController = Cast<ABossAIController>(GetController());
	AIController->StopAI();
	AIController->StartAI();
}

void ABossMonster::SetCanDashTrue()
{
	bCanDash = true;
	auto AIController = Cast<ABossAIController>(GetController());
	AIController->StopAI();
	AIController->StartAI();
}
