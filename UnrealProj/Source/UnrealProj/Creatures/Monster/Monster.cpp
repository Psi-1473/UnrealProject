#include "Monster.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "../../Stat/MonsterStatComponent.h"
#include "../../Animations/Monster/MonsterAnimInstance.h"
#include "Components/WidgetComponent.h"
#include "Components/SceneComponent.h"
#include "../../TextRender/DamageText.h"
#include "../../Widgets/Components/Widget_HpBar.h"
#include "../../MyGameInstance.h"
#include "../Player/MyPlayer.h"
#include "../../Stat/PlayerStatComponent.h"
#include "../../Inventory/Inventory.h"
#include "../../AI/MonsterAIController.h"

AMonster::AMonster()
{
	PrimaryActorTick.bCanEverTick = true;
	StatComponent = CreateDefaultSubobject<UMonsterStatComponent>(TEXT("StatComponent"));
	DamageTextComp = CreateDefaultSubobject<USceneComponent>(TEXT("DamageTextComponent"));
	DamageTextComp->SetRelativeLocation(FVector(50.f, 0.f, 0.f));

	
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Monster"));
	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -88.f));
	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
	GetMesh()->SetCollisionProfileName("NoCollision");
	auto Movement = Cast<UCharacterMovementComponent>(GetMovementComponent());
	Movement->MaxWalkSpeed = 200.f;
	SetHpBar();
	static ConstructorHelpers::FClassFinder<UUserWidget> WIDGETHP(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/02_Blueprints/Widget/Components/WBP_HpBar.WBP_HpBar_C'"));
	if (WIDGETHP.Succeeded())
	{
		HpBar->SetWidgetClass(WIDGETHP.Class);
		HpBar->SetDrawSize(FVector2d(150.f, 50.f));
	}

}

void AMonster::BeginPlay()
{
	Super::BeginPlay();
}

void AMonster::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	UE_LOG(LogTemp, Warning, TEXT("POST INIT"));
	if (GetMesh()->GetAnimInstance() != nullptr)
	{
		AnimInst = Cast<UMonsterAnimInstance>(GetMesh()->GetAnimInstance());
		AnimInst->OnDied.AddUObject(this, &AMonster::DestroyObject);
	}
	HpBar->InitWidget();
	auto Bar = Cast<UWidget_HpBar>(HpBar->GetUserWidgetObject());
	if (Bar != nullptr)
		Bar->BindHp(StatComponent);
}

void AMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FString AMonster::GetObjectName()
{
	FString MyName = GetClass()->GetName(); // BP_Zombie_C
	int StartIndex = 3; // BP_ ���� ù ������ Index�� 3
	int Count = MyName.Len() - StartIndex - 2; // Len - StartIndex = Zombie_C, -2�� �� ���ָ� Zombie
	MyName = MyName.Mid(StartIndex, Count); // Zombie
	return MyName;
}

void AMonster::AttackTarget(AMyPlayer* Target)
{
	AnimInst->PlayAttackMontage();
}

float AMonster::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
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

void AMonster::Die(AMyPlayer* Player)
{
	auto AIController = Cast<AMonsterAIController>(GetController());

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("NoCollision"));
	AIController->StopAI();
	bDeath = true;
	AnimInst->StopAllMontages(1.f);

	Player->GetStatComponent()->AddExp(StatComponent->GetExp());
	Player->GetInventory()->AddGold(StatComponent->GetGold());
}

void AMonster::DestroyObject()
{
	FTimerDelegate TimeCallback;
	TimeCallback.BindLambda([this] {
		this->Destroy();
		GetWorldTimerManager().ClearTimer(DestroyTimerHandle); 
		});
	GetWorldTimerManager().SetTimer(DestroyTimerHandle, TimeCallback, 5.f, false);
	
	
}

void AMonster::SetHpBar()
{
	HpBar = CreateDefaultSubobject<UWidgetComponent>(TEXT("HPBAR"));
	HpBar->SetupAttachment(GetMesh());
	HpBar->SetRelativeLocation(FVector(0.f, 0.f, 160.f));
	HpBar->SetWidgetSpace(EWidgetSpace::Screen);
}

void AMonster::PopupDamageText(float Damage)
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = GetInstigator();

	auto DamageText = GetWorld()->SpawnActor<ADamageText>(ADamageText::StaticClass(),
		GetActorLocation() + DamageTextComp->GetRelativeLocation(),
		DamageTextComp->GetRelativeRotation(),
		SpawnParams);

	DamageText->SetDamageText(Damage);
}


