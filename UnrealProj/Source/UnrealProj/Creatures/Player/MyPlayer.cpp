// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayer.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "../../Animations/Player/PlayerAnim.h"
#include "../../State/StateMachine.h"
#include "../../Items/Weapons/Weapon.h"
#include "../../Projectiles/Projectile.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "../Monster/Monster.h"
#include "Engine/DamageEvents.h"
#include "../../Stat/PlayerStatComponent.h"
#include "../../Skills/Components/PlayerSkillComponent.h"
#include "../../Skills/Player/Sword/PlayerSkill_Sword_First.h"
#include "../../Skills/Player/Sword/PlayerSkill_Sword_Second.h"
#include "../../Skills/Player/Bow/PlayerSkill_Bow_First.h"
#include "../../Skills/Player/Bow/PlayerSkill_Bow_Second.h"
#include "../../Inventory/Inventory.h"
#include "Kismet/GameplayStatics.h"
#include "../Npc/Npc.h"
#include "../../MyGameMode.h"




AMyPlayer::AMyPlayer()
{
	PrimaryActorTick.bCanEverTick = true;
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Player"));
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
		AnimClasses[(int)WEAPONTYPE::WEAPON_ARROW] = AnimAsset2.Class;


	SetDefaultCamera();
	SetWeaponSocket();

	StateMachine = NewObject<UStateMachine>();
	StateMachine->SetOwner(this);

	StatComponent = CreateDefaultSubobject<UPlayerStatComponent>(TEXT("StatComponent"));
	SkillComponent = CreateDefaultSubobject<UPlayerSkillComponent>(TEXT("SkillComponent"));
	Inventory = CreateDefaultSubobject<UInventory>(TEXT("Inventory"));

}

void AMyPlayer::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	SetAnimByWeapon(WEAPONTYPE::WEAPON_ARROW);
}

void AMyPlayer::BeginPlay()
{
	Super::BeginPlay();
	Inventory->SetOwnerPlayer(this);
	SkillComponent->SetOwnerPlayer(this);
	GInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	GInstance->GetUIMgr()->SetController(Cast<APlayerController>(GetController()));


	// TEMP : 무기 장착 : 무기 데이터 받기 전까지 임시로 하드코딩
	AWeapon* NewWeapon = NewObject<AWeapon>();
	NewWeapon->SetWeaponType(WEAPONTYPE::WEAPON_ARROW);
	NewWeapon->SetId(0);
	NewWeapon->SetItemMesh();
	EquipWeapon(NewWeapon);


	//	TEMP : Skill Sword
	UPlayerSkill_Sword_First* NewSkill = NewObject<UPlayerSkill_Sword_First>();
	SkillComponent->AddSkill(NewSkill);
	UPlayerSkill_Sword_Second* NewSkill2 = NewObject<UPlayerSkill_Sword_Second>();
	SkillComponent->AddSkill(NewSkill2);
	//	SKILL: ARROW
	UPlayerSkill_Bow_First* NewBowSkill = NewObject<UPlayerSkill_Bow_First>();
	SkillComponent->AddSkill(NewBowSkill);
	UPlayerSkill_Bow_Second* NewBowSkill2 = NewObject<UPlayerSkill_Bow_Second>();
	SkillComponent->AddSkill(NewBowSkill2);


	if (StateMachine == nullptr)
	{
		StateMachine = NewObject<UStateMachine>();
		StateMachine->SetOwner(this);
	}

	auto GMode = UGameplayStatics::GetGameMode(GetWorld());
	auto GameMode = Cast<AMyGameMode>(GMode);

	if (GameMode == nullptr) return;
	GameMode->BindPlayer(this);


}

void AMyPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (StateMachine != nullptr)
		StateMachine->OnUpdate();
}

void AMyPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

float AMyPlayer::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{

	StatComponent->OnAttacked(Damage);
	//auto CauserPlayer = Cast<AMyPlayer>(DamageCauser); Causer를 몬스터로 하고
	//PopupDamageText(Damage); 데미지 팝업 띄우기

	//if (StatComponent->GetHp() <= 0)
	//	Die(CauserPlayer);
	// return -1;


	return Damage;
}

void AMyPlayer::OnDamaged(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser, AttackType Type)
{
	TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
	// HP UI 업데이트
	// -1을 TakeDamage가 리턴하면 종료 (플레이어 죽었다는 뜻)

	// 어택 타입에 따라 경직, 날리기, 노경직 선택 (애니메이션)
	switch (Type)
	{
	case AttackType::NORMAL:
		break;
	case AttackType::STRONG:
		// 경직 애니메이션 틀기
		break;
	}

}

void AMyPlayer::Die()
{
}

UCharacterState* AMyPlayer::GetState()
{
	if (StateMachine == nullptr)
		return nullptr;

	return StateMachine->GetState();
}

UCharacterState* AMyPlayer::GetSpecificState(STATE Value)
{
	return StateMachine->GetState(Value);
}

void AMyPlayer::SetState(STATE Value)
{
	StateMachine->SetState(Value);
}

void AMyPlayer::EquipWeapon(AWeapon* _Weapon)
{
	EquipedWeapon = _Weapon;

	if (_Weapon->GetIsRight())
	{
		LWeapon->SetStaticMesh(nullptr);
		RWeapon->SetStaticMesh(_Weapon->GetStaticMesh());
	}
	else
	{
		RWeapon->SetStaticMesh(nullptr);
		LWeapon->SetStaticMesh(_Weapon->GetStaticMesh());
	}

	SetAnimByWeapon(_Weapon->GetType());
}

void AMyPlayer::AttackCheck(float UpRange, float FrontRange, float SideRange)
{
	TArray<FHitResult> HitResults;
	FCollisionQueryParams Params(NAME_None, false, this);

	float Start = 100.f;

	FVector StartVector = GetActorLocation() + GetActorForwardVector() * Start;
	FVector EndVector = GetActorLocation() + GetActorForwardVector() * (FrontRange + Start);


	bool bResult = GetWorld()->SweepMultiByChannel(
		OUT HitResults,
		StartVector,
		EndVector,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel5,
		FCollisionShape::MakeBox(FVector(SideRange, UpRange, FrontRange)),//측면, 높이, 정면
		Params);

	FVector Vec = GetActorForwardVector() * Start;
	FVector Center = StartVector + (EndVector - StartVector) / 2;
	FQuat Rotation = FRotationMatrix::MakeFromZ(Vec).ToQuat();
	FColor DrawColor;
	if (bResult)
		DrawColor = FColor::Green;
	else
		DrawColor = FColor::Red;

	DrawDebugBox(GetWorld(), Center, FVector(SideRange, UpRange, FrontRange), Rotation, DrawColor, false, 2.f);

	if (bResult && !HitResults.IsEmpty())
	{
		for (FHitResult HitResult : HitResults)
		{
			UE_LOG(LogTemp, Log, TEXT("Hit Actor : %s"), *HitResult.GetActor()->GetName());
			AMonster* Enemy = Cast<AMonster>(HitResult.GetActor());
			FDamageEvent DamageEvent;
			if (Enemy == nullptr)
				return;
			Enemy->TakeDamage(10.f, DamageEvent, GetController(), this); //Temp
		}
	}
}

void AMyPlayer::Interact()
{
	if (InteractingNpc == nullptr)
		return;

	InteractingNpc->Interact();
}


void AMyPlayer::SetDefaultCamera()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

	SpringArm->SetupAttachment(RootComponent);
	SpringArm->SetRelativeLocationAndRotation(FVector(.0f, .0f, 50.f), FRotator(0.f, .0f, .0f));
	SpringArm->TargetArmLength = 500.f;
	SpringArm->bUsePawnControlRotation = true;

	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
}

void AMyPlayer::SetWeaponSocket()
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

void AMyPlayer::SetAnimByWeapon(WEAPONTYPE Type)
{
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	GetMesh()->SetAnimClass(AnimClasses[(int)Type]);
	AnimInst = Cast<UPlayerAnim>(GetMesh()->GetAnimInstance());
	AnimInst->WeaponType = Type;
}

