#include "Monster.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "../../Stat/MonsterStatComponent.h"
#include "../../Animations/Monster/EnemyAnimInstance.h"
#include "Components/SceneComponent.h"
#include "../../TextRender/DamageText.h"
#include "../../MyGameInstance.h"
#include "../Player/MyPlayer.h"
#include "../../Stat/PlayerStatComponent.h"
#include "../../Inventory/Inventory.h"
#include "../../AI/MonsterAIController.h"
#include "../../Helpers/AttackChecker.h"
#include "Kismet/GameplayStatics.h"
#include "Components/AudioComponent.h"
#include "Components/WidgetComponent.h"
#include "Kismet/KismetMathLibrary.h"

AMonster::AMonster()
{
	InitTargetUI();
	static ConstructorHelpers::FClassFinder<UUserWidget> TARGET(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/02_Blueprints/Widget/Components/WBP_TargetUI.WBP_TargetUI_C'"));
	if (TARGET.Succeeded())
	{
		TargetUI->SetWidgetClass(TARGET.Class);
		TargetUI->SetDrawSize(FVector2d(150.f, 150.f));
	}

	PrimaryActorTick.bCanEverTick = true;
	StatComponent = CreateDefaultSubobject<UMonsterStatComponent>(TEXT("StatComponent"));
	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
	DamageTextComp = CreateDefaultSubobject<USceneComponent>(TEXT("DamageTextComponent"));
	DamageTextComp->SetRelativeLocation(FVector(50.f, 0.f, 0.f));
	InitWeaponSocket();
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Monster"));
	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -88.f));
	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
	GetMesh()->SetCollisionProfileName("NoCollision");

	auto Movement = Cast<UCharacterMovementComponent>(GetMovementComponent());
	Movement->MaxWalkSpeed = 200.f;
	AudioComponent->SetupAttachment(RootComponent);
	TargetUI->SetVisibility(false);
}

void AMonster::BeginPlay()
{
	Super::BeginPlay();
}
void AMonster::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}
void AMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

int AMonster::GetObjectId()
{
	FString MyName = GetClass()->GetName(); // BP_Zombie_C
	int StartIndex = 10; // BP_Monster 이후 첫 글자의 Index가 3
	int Count = MyName.Len() - StartIndex - 2; // Len - StartIndex = Zombie_C, -2를 더 해주면 Zombie
	MyName = MyName.Mid(StartIndex, Count); // Zombie
	UE_LOG(LogTemp, Warning, TEXT("Mob Id %s"), *MyName);
	int Value = FCString::Atof(*MyName);
	
	return Value;
}

void AMonster::AttackTarget(AMyPlayer* Target)
{
	FVector TargetLoc = Target->GetActorLocation();
	TargetLoc.Z = GetActorLocation().Z;
	FRotator Rot = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), TargetLoc);

	SetActorRotation(Rot);
	AnimInst->PlayAttackMontage();
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

void AMonster::AttackMelee()
{
	float Start = 100.f;
	TArray<FHitResult> HitResults;
	FVector RangeVector(50.f, 50.f, 50.f);
	FCollisionQueryParams Params(NAME_None, false, this);

	HitResults = UAttackChecker::MonsterCubeCheck(RangeVector, Start, ECC_GameTraceChannel6, this);
	UAttackChecker::ApplyHitDamageToActors(10.f, this, HitResults, AttackType::NORMAL);
}

void AMonster::AttackBow()
{
}

void AMonster::AttackMagic()
{
}

void AMonster::SetTargetUI(bool Value)
{
	if(TargetUI == nullptr)
		return;
	TargetUI->SetVisibility(Value);
}


void AMonster::InitTargetUI()
{
	TargetUI = CreateDefaultSubobject<UWidgetComponent>(TEXT("TARGETUI"));
	TargetUI->SetupAttachment(GetMesh());
	TargetUI->SetRelativeLocation(FVector(0.f, 0.f, 60.f));
	TargetUI->SetWidgetSpace(EWidgetSpace::Screen);
}

void AMonster::InitWeaponSocket()
{
	RWeapon = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RWEAPON"));
	LWeapon = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LWEAPON"));

	FName RWeaponSocket(TEXT("Weapon_R"));
	FName LWeaponSocket(TEXT("Weapon_L"));

	if (GetMesh()->DoesSocketExist(RWeaponSocket))
		RWeapon->SetupAttachment(GetMesh(), RWeaponSocket);

	if (GetMesh()->DoesSocketExist(LWeaponSocket))
		LWeapon->SetupAttachment(GetMesh(), LWeaponSocket);
}





