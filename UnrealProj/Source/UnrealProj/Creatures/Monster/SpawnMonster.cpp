// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnMonster.h"
#include "../../AI/MonsterAIController.h"
#include "../Player/MyPlayer.h"
#include "../../Animations/Monster/MonsterAnimInstance.h"
#include "../../Animations/Monster/EnemyAnimInstance.h"
#include "../../Stat/PlayerStatComponent.h"
#include "Components/CapsuleComponent.h"
#include "../../Inventory/Inventory.h"
#include "../../Stat/MonsterStatComponent.h"
#include "../../Widgets/Components/Widget_HpBar.h"
#include "../../Widgets/Components/Widget_MonsterMark.h"
#include "Components/WidgetComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine/DamageEvents.h"
#include "../../Helpers/AttackChecker.h"
#include "../../MyGameInstance.h"
#include "../../DEFINE.h"
#include "Particles/ParticleSystem.h"
#include "Kismet/GameplayStatics.h"

ASpawnMonster::ASpawnMonster()
{
	AIControllerClass = AMonsterAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	SetHpBar();
	SetMarkUI();
	static ConstructorHelpers::FClassFinder<UUserWidget> WIDGETHP(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/02_Blueprints/Widget/Components/WBP_HpBar.WBP_HpBar_C'"));
	static ConstructorHelpers::FClassFinder<UUserWidget> WIDGETMARK(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/02_Blueprints/Widget/Components/WBP_MonsterMark.WBP_MonsterMark_C'"));
	if (WIDGETHP.Succeeded())
	{
		HpBar->SetWidgetClass(WIDGETHP.Class);
		HpBar->SetDrawSize(FVector2d(150.f, 50.f));
	}

	if (WIDGETHP.Succeeded())
	{
		MarkUI->SetWidgetClass(WIDGETMARK.Class);
		MarkUI->SetDrawSize(FVector2d(70.f, 70.f));
	}

	GetMesh()->LDMaxDrawDistance = 20000.f;
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
	Cast<UMonsterAnimInstance>(AnimInst)->OnDied.AddUObject(this, &ASpawnMonster::DestroyObject);
	InitWeaponSocket();

}

void ASpawnMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CheckDistance();
}


void ASpawnMonster::SucceedFindingTarget()
{
	// 1. 느낌표 애니메이션 실행
	//UWidgetAnimation* WidgetAnim = 
	MarkUI->SetVisibility(true);
	auto Widget = Cast<UWidget_MonsterMark>(MarkUI->GetUserWidgetObject());
	Widget->PlayAnim();
	// 2. bChase 켜기
	bChase = true;
}

void ASpawnMonster::TargetOutOfRange()
{
	// bChase 끄기
	//MarkUI->SetVisibility(false);
	bChase = false;
}

void ASpawnMonster::OnDamaged(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser, UParticleSystem* Particle, AttackType Type)
{
	// 1. Damage Type에 따라 처리
	UE_LOG(LogTemp, Warning, TEXT("Spawn Monster Damaged"));
	if (Particle != nullptr)
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Particle, GetActorLocation());

	auto AIController = Cast<AMonsterAIController>(GetController());
	AIController->StopAI();
	AnimInst->PlayDamagedMontage();

	int DamageValue = FMath::RandRange(Damage / 2, Damage);
	StatComponent->OnAttacked(DamageValue);

	auto CauserPlayer = Cast<AMyPlayer>(DamageCauser);
	Attacker = CauserPlayer;

	RevealHpBar();
	PopupDamageText(DamageValue);

	GetWorldTimerManager().ClearTimer(HideHpBarTimer);
	GetWorldTimerManager().SetTimer(HideHpBarTimer, this, &ASpawnMonster::HideHpBar, 15.f, false);

	if (StatComponent->GetHp() <= 0)
		Die(CauserPlayer);
}

void ASpawnMonster::Die(AMyPlayer* Player)
{
	auto AIController = Cast<AMonsterAIController>(GetController());
	DropItem();
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
	switch (StatComponent->GetAttackType())
	{
	case ENEMY_ATTACKT_TYPE::MELEE:
		AttackMelee();
		break;
	case ENEMY_ATTACKT_TYPE::BOW:
		AttackBow();
		break;
	case ENEMY_ATTACKT_TYPE::MAGIC:
		AttackMagic();
		break;
	default:
		break;
	}
}

void ASpawnMonster::SetHpBar()
{
	HpBar = CreateDefaultSubobject<UWidgetComponent>(TEXT("HPBAR"));
	HpBar->SetupAttachment(GetMesh());
	HpBar->SetRelativeLocation(FVector(0.f, 0.f, 160.f));
	HpBar->SetWidgetSpace(EWidgetSpace::Screen);
}

void ASpawnMonster::SetMarkUI()
{
	MarkUI = CreateDefaultSubobject<UWidgetComponent>(TEXT("MARK"));
	MarkUI->SetupAttachment(GetMesh());
	MarkUI->SetRelativeLocation(FVector(0.f, 0.f, 230.f));
	MarkUI->SetWidgetSpace(EWidgetSpace::Screen);
	MarkUI->SetVisibility(false);
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
