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

void ASpawnMonster::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	HpBar->InitWidget();
	auto Bar = Cast<UWidget_HpBar>(HpBar->GetUserWidgetObject());
	if (Bar != nullptr)
		Bar->BindHp(StatComponent);

	AnimInst = Cast<UMonsterAnimInstance>(GetMesh()->GetAnimInstance());
	AnimInst->OnDied.AddUObject(this, &ASpawnMonster::DestroyObject);
}

void ASpawnMonster::AttackTarget(AMyPlayer* Target)
{
	AnimInst->PlayAttackMontage();
}

float ASpawnMonster::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	auto AIController = Cast<AMonsterAIController>(GetController());
	AIController->StopAI();
	AnimInst->PlayDamagedMontage();
	StatComponent->OnAttacked(Damage);

	auto CauserPlayer = Cast<AMyPlayer>(DamageCauser);

	PopupDamageText(Damage);
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

void ASpawnMonster::SetHpBar()
{
	HpBar = CreateDefaultSubobject<UWidgetComponent>(TEXT("HPBAR"));
	HpBar->SetupAttachment(GetMesh());
	HpBar->SetRelativeLocation(FVector(0.f, 0.f, 160.f));
	HpBar->SetWidgetSpace(EWidgetSpace::Screen);
}
