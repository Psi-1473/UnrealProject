// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayer.h"
#include "MyPlayerController.h"
#include "../../CameraShakes/HitCameraShake.h"
#include "../../CameraShakes/SkillHitCameraShake.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "../../Animations/Player/PlayerAnim.h"
#include "../../State/StateMachine.h"
#include "../../State/BuffComponent.h"
#include "../../Items/Weapons/Weapon.h"
#include "../../Managers/SoundManager.h"
#include "../../Projectiles/Projectile.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "../Monster/Monster.h"
#include "Engine/DamageEvents.h"
#include "../../Stat/PlayerStatComponent.h"
#include "../../Skills/Components/PlayerSkillComponent.h"
#include "../../Inventory/Inventory.h"
#include "../../Inventory/EquipItemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "../Npc/Npc.h"
#include "../../MyGameMode.h"
#include "../../MyGameInstance.h"
#include "LegacyCameraShake.h"
#include "Components/AudioComponent.h"
#include "../../Widgets/Widget_PlayerMain.h"
#include "../../Helpers/AttackChecker.h"
#include "../../ActorComponent/PlayerQuestComponent.h"
#include "../../Triggers/AreaBox.h"
#include "../../Items/Weapons/Bow.h"
#include "../../Widgets/Popup/Widget_Revive.h"

AMyPlayer::AMyPlayer()
{
	PrimaryActorTick.bCanEverTick = true;
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Player"));
	InitAssets();
	InitDefaultCamera();
	InitWeaponSocket();
	CreateComponents();
}

void AMyPlayer::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	SetAnimByWeapon(WEAPONTYPE::WEAPON_BOW);
}
void AMyPlayer::BeginPlay()
{
	Super::BeginPlay();
	InitializeComponents();
	SetEngineVariables();

	// TEMP : 무기 장착 : 무기 데이터 받기 전까지 임시로 하드코딩
	AWeapon* NewWeapon = NewObject<ABow>();
	NewWeapon->SetWeaponType(WEAPONTYPE::WEAPON_BOW);
	NewWeapon->SetId(0);
	NewWeapon->SetItemMesh();
	EquipComponent->EquipWeapon(NewWeapon);
	//

	SkillComponent->SkillsInit();
}
void AMyPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (StateMachine != nullptr)
		StateMachine->OnUpdate();

	if (SkillComponent != nullptr)
		SkillComponent->Update(DeltaTime);

	if (BuffComponent != nullptr)
		BuffComponent->UpdateDebuff();
}

void AMyPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}


void AMyPlayer::OnDamaged(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser, AttackType Type)
{
	StatComponent->OnAttacked(Damage);
	auto CauserMonster = Cast<AMonster>(DamageCauser);
	//PopupDamageText(Damage); 데미지 팝업 띄우기

	if (StatComponent->GetHp() <= 0)
	{
		Die();
		return;
	}

	if (Type == AttackType::NORMAL)
		ShakeCamera(SHAKE_BASIC);
	else
	{
		AnimInst->StopAllMontages(0.f);
		AnimInst->SetComboAndStepZero();
		switch (Type)
		{
		case AttackType::STRONG:
			ShakeCamera(SHAKE_SKILL);
			StateMachine->SetState(STATE::DAMAGED);
			break;
		case AttackType::THRUST:
			break;
		case AttackType::PULLED:
			ShakeCamera(SHAKE_BASIC);
			AnimInst->PlayDamagedMontage();
			break;
		case AttackType::DOWN:
			StateMachine->SetState(STATE::KNOCKED);
			break;
		case AttackType::HITANDFALL:
			StateMachine->SetState(STATE::HITANDFALL);
			break;
		}
	}
}

void AMyPlayer::Die()
{
	if(GetStateMachine()->GetState()->GetState() == STATE::DEAD)
		return;

	StateMachine->SetState(STATE::DEAD);
	auto Widget = GInstance->GetUIMgr()->PopupUI(GetWorld(), UIType::Revive);
	auto ReviveWidget = Cast<UWidget_Revive>(Widget);
	ReviveWidget->SetPlayer(this);
}

void AMyPlayer::Revive()
{
	FVector SpawnLocation(7170.f, -6250.f, 192.f);
	SetActorLocation(SpawnLocation);
	GetStateMachine()->SetState(STATE::RESPAWN);
	StatComponent->SetHp(StatComponent->GetMaxHp());
	StatComponent->SetMp(StatComponent->GetMaxMp());
}


void AMyPlayer::AttackCheck(float UpRange, float FrontRange, float SideRange)
{
	float Start = 100.f;
	FVector RangeVector(SideRange, UpRange, FrontRange);
	TArray<FHitResult> HitResults;

	HitResults = UAttackChecker::PlayerCubeCheckMulti(RangeVector, Start, ECC_GameTraceChannel5, this);
	UAttackChecker::ApplyHitDamageToActors(10.f, this, HitResults);
}
void AMyPlayer::Interact()
{
	if (InteractObj == nullptr)
		return;

	InteractObj->Interact(this);
}

void AMyPlayer::ShakeCamera(CameraShakeType Type)
{
	if (Type == SHAKE_BASIC)
	{
		GetController<AMyPlayerController>()->ClientPlayCameraShake(UHitCameraShake::StaticClass(),
			1.f, ECameraAnimPlaySpace::CameraLocal);
	}
	if (Type == SHAKE_SKILL)
	{
		GetController<AMyPlayerController>()->ClientPlayCameraShake(USkillHitCameraShake::StaticClass(),
			1.f, ECameraAnimPlaySpace::CameraLocal);
	}
}

void AMyPlayer::ShakeCamera(TSubclassOf<class ULegacyCameraShake> Type)
{
	GetController<AMyPlayerController>()->ClientPlayCameraShake(Type,
		1.f, ECameraAnimPlaySpace::CameraLocal);
}

void AMyPlayer::SetAnimByWeapon(WEAPONTYPE Type)
{
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	GetMesh()->SetAnimClass(AnimClasses[(int)Type]);
	AnimInst = Cast<UPlayerAnim>(GetMesh()->GetAnimInstance());
	AnimInst->WeaponType = Type;

	auto MyGamemode = Cast<AMyGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (MyGamemode == nullptr) return;

	auto HUD = Cast<UWidget_PlayerMain>(MyGamemode->GetCurrentWidget());
	if (HUD == nullptr) return;

	if (AnimInst->WeaponType == WEAPONTYPE::WEAPON_BOW)
		HUD->SetCrossHair(true);

	if (AnimInst->WeaponType == WEAPONTYPE::WEAPON_SWORD)
		HUD->SetCrossHair(false);
}

void AMyPlayer::InitDefaultCamera()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

	SpringArm->SetupAttachment(RootComponent);
	SpringArm->SetRelativeLocationAndRotation(FVector(.0f, .0f, 50.f), FRotator(0.f, .0f, .0f));
	SpringArm->TargetArmLength = 500.f;
	SpringArm->bUsePawnControlRotation = true;

	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
}
void AMyPlayer::InitWeaponSocket()
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
void AMyPlayer::InitAssets()
{
	AnimClasses.Init(nullptr, (int)WEAPONTYPE::WEAPON_END);
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonAurora/Characters/Heroes/Aurora/Meshes/Aurora.Aurora'"));
	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimAsset(TEXT("/Script/Engine.AnimBlueprint'/Game/02_Blueprints/Animations/Player/ABP_Player.ABP_Player_C'"));
	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimAsset2(TEXT("/Script/Engine.AnimBlueprint'/Game/02_Blueprints/Animations/Player/ABP_Player_Arrow.ABP_Player_Arrow_C'"));

	if (MeshAsset.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(MeshAsset.Object);
		GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -88.f));
		GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, -0.f));
		GetMesh()->SetCollisionProfileName("NoCollision");
	}
	if (AnimAsset.Succeeded())
		AnimClasses[(int)WEAPONTYPE::WEAPON_SWORD] = AnimAsset.Class;
	if (AnimAsset2.Succeeded())
		AnimClasses[(int)WEAPONTYPE::WEAPON_BOW] = AnimAsset2.Class;
}
void AMyPlayer::CreateComponents()
{
	StateMachine = NewObject<UStateMachine>();
	StateMachine->SetOwner(this);

	StatComponent = CreateDefaultSubobject<UPlayerStatComponent>(TEXT("StatComponent"));
	SkillComponent = CreateDefaultSubobject<UPlayerSkillComponent>(TEXT("SkillComponent"));
	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
	QuestComponent = CreateDefaultSubobject<UPlayerQuestComponent>(TEXT("QuestComponent"));
	BuffComponent = CreateDefaultSubobject<UBuffComponent>(TEXT("BuffComponent"));
	EquipComponent = CreateDefaultSubobject<UEquipItemComponent>(TEXT("EquipComponent"));
	Inventory = CreateDefaultSubobject<UInventory>(TEXT("Inventory"));
	AudioComponent->SetupAttachment(RootComponent);
}
void AMyPlayer::InitializeComponents()
{
	Inventory->SetOwnerPlayer(this);
	SkillComponent->SetOwnerPlayer(this);
	BuffComponent->Init();
	EquipComponent->SetInfo(this);
	if (StateMachine == nullptr)
	{
		StateMachine = NewObject<UStateMachine>();
		StateMachine->SetOwner(this);
		StateMachine->SetState(STATE::IDLE);
	}

}
void AMyPlayer::SetEngineVariables()
{
	GInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	GInstance->GetUIMgr()->SetController(Cast<APlayerController>(GetController()));
	auto GMode = UGameplayStatics::GetGameMode(GetWorld());
	auto GameMode = Cast<AMyGameMode>(GMode);

	if (GameMode == nullptr) return;
	GameMode->BindPlayer(this);
	GInstance->GetSoundMgr()->Init(GetWorld());
}

 
