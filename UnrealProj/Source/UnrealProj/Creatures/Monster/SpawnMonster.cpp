// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnMonster.h"
#include "../../AI/MonsterAIController.h"
#include "../Player/MyPlayer.h"
#include "../../Animations/Monster/MonsterAnimInstance.h"
#include "../../Stat/PlayerStatComponent.h"
#include "Components/CapsuleComponent.h"
#include "../../Inventory/Inventory.h"
#include "../../Stat/MonsterStatComponent.h"
#include "../../Widgets/Components/Widget_HpBar.h"
#include "Components/WidgetComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine/DamageEvents.h"
#include "../../Helpers/AttackChecker.h"
#include "../../MyGameInstance.h"

ASpawnMonster::ASpawnMonster()
{
	AIControllerClass = AMonsterAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	SetHpBar();
	static ConstructorHelpers::FClassFinder<UUserWidget> WIDGETHP(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/02_Blueprints/Widget/Components/WBP_HpBar.WBP_HpBar_C'"));
	if (WIDGETHP.Succeeded())
	{
		HpBar->SetWidgetClass(WIDGETHP.Class);
		HpBar->SetDrawSize(FVector2d(150.f, 50.f));
	}
}

void ASpawnMonster::BeginPlay()
{
	Super::BeginPlay();
	HpBar->SetVisibility(false);
}

void ASpawnMonster::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	HpBar->InitWidget();
	auto Bar = Cast<UWidget_HpBar>(HpBar->GetUserWidgetObject());
	if (Bar != nullptr)
		Bar->BindHp(StatComponent);

	AnimInst = Cast<UMonsterAnimInstance>(GetMesh()->GetAnimInstance());
	if (AnimInst == nullptr) return;
	AnimInst->OnDied.AddUObject(this, &ASpawnMonster::DestroyObject);


}

void ASpawnMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CheckDistance();
}

void ASpawnMonster::AttackTarget(AMyPlayer* Target)
{
	FRotator Rot = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), Target->GetActorLocation());
	SetActorRotation(Rot);
	AnimInst->PlayAttackMontage();
}

void ASpawnMonster::OnDamaged(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser, AttackType Type)
{
	// 1. Damage Type에 따라 처리

	TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
}




float ASpawnMonster::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	auto AIController = Cast<AMonsterAIController>(GetController());
	AIController->StopAI();
	AnimInst->PlayDamagedMontage();
	StatComponent->OnAttacked(Damage);

	auto CauserPlayer = Cast<AMyPlayer>(DamageCauser);
	Attacker = CauserPlayer;
	RevealHpBar();
	PopupDamageText(Damage);
	GetWorldTimerManager().ClearTimer(AttackerTimer);
	GetWorldTimerManager().SetTimer(AttackerTimer, this, &ASpawnMonster::HideHpBar, 15.f, false);
	if (StatComponent->GetHp() <= 0)
		Die(CauserPlayer);
	return Damage;
}

void ASpawnMonster::Die(AMyPlayer* Player)
{
	auto AIController = Cast<AMonsterAIController>(GetController());

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("NoCollision"));
	AIController->StopAI();
	bDeath = true;
	AnimInst->StopAllMontages(1.f);

	Player->GetStatComponent()->AddExp(StatComponent->GetExp());
	Player->GetInventory()->AddGold(StatComponent->GetGold());
	auto GInstance = Cast<UMyGameInstance>(GetGameInstance());
	GInstance->CheckQuest(QUEST_HUNT, StatComponent->GetId(), Player);

}

void ASpawnMonster::DestroyObject()
{
	FTimerDelegate TimeCallback;
	TimeCallback.BindLambda([this] {
		this->Destroy();
		GetWorldTimerManager().ClearTimer(DestroyTimerHandle);
		});
	GetWorldTimerManager().SetTimer(DestroyTimerHandle, TimeCallback, 5.f, false);

}

void ASpawnMonster::AttackCheck()
{
	float Start = 100.f;
	TArray<FHitResult> HitResults;
	FVector RangeVector(50.f, 50.f, 50.f);
	FCollisionQueryParams Params(NAME_None, false, this);

	HitResults = UAttackChecker::MonsterCubeCheck(RangeVector, Start, ECC_GameTraceChannel6, this);
	UAttackChecker::ApplyHitDamageToActors(10.f, this, HitResults, AttackType::NORMAL);
}

void ASpawnMonster::SetHpBar()
{
	HpBar = CreateDefaultSubobject<UWidgetComponent>(TEXT("HPBAR"));
	HpBar->SetupAttachment(GetMesh());
	HpBar->SetRelativeLocation(FVector(0.f, 0.f, 160.f));
	HpBar->SetWidgetSpace(EWidgetSpace::Screen);
}

void ASpawnMonster::RevealHpBar()
{
	HpBar->SetVisibility(true);
}

void ASpawnMonster::CheckDistance()
{
	if (Attacker == nullptr)
		return;

	if (GetDistanceTo(Cast<AActor>(Attacker)) >= 2000.f)
		HideHpBar();
}

void ASpawnMonster::HideHpBar()
{
	Attacker = nullptr;
	HpBar->SetVisibility(false);
}
