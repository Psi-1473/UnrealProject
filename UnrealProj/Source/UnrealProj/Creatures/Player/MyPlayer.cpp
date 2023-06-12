// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayer.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "../../Animations/Player/PlayerAnim.h"
#include "../../State/StateMachine.h"
#include "../../Items/Weapons/Weapon.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"




AMyPlayer::AMyPlayer()
{
	PrimaryActorTick.bCanEverTick = true;
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Player"));
	AnimClasses.Init(nullptr, WEAPON_END);

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonAurora/Characters/Heroes/Aurora/Meshes/Aurora.Aurora'"));
	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimAsset (TEXT("/Script/Engine.AnimBlueprint'/Game/02_Blueprints/Animations/Player/ABP_Player.ABP_Player_C'"));
	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimAsset2 (TEXT("/Script/Engine.AnimBlueprint'/Game/02_Blueprints/Animations/Player/ABP_Player_Arrow.ABP_Player_Arrow_C'"));

	if (MeshAsset.Succeeded())
	{
		GetMesh()->SkeletalMesh = MeshAsset.Object;
		GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -88.f));
		GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, -0.f));
	}

	if (AnimAsset.Succeeded())
		AnimClasses[WEAPON_SWORD] = AnimAsset.Class;
	if (AnimAsset2.Succeeded())
		AnimClasses[WEAPON_ARROW] = AnimAsset2.Class;

	
	SetDefaultCamera();
	SetWeaponSocket();
	
	StateMachine = NewObject<UStateMachine>();
	StateMachine->SetOwner(this);
}

void AMyPlayer::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	SetAnimByWeapon(WEAPON_ARROW);
}

void AMyPlayer::BeginPlay()
{
	Super::BeginPlay();
	

	// 무기 장착 : 무기 데이터 받기 전까지 임시로 하드코딩
	UWeapon* NewWeapon = NewObject<UWeapon>();
	NewWeapon->Init(WEAPON_ARROW, 0);
	EquipWeapon(NewWeapon);
	// 무기장착
	

	if (StateMachine == nullptr)
	{
		StateMachine = NewObject<UStateMachine>();
		StateMachine->SetOwner(this);
	}
}

void AMyPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(StateMachine != nullptr)
		StateMachine->OnUpdate();
}

void AMyPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

UCharacterState* AMyPlayer::GetState()
{
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

void AMyPlayer::EquipWeapon(UWeapon* _Weapon)
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
	GetMesh()->SetAnimClass(AnimClasses[Type]);
	AnimInst = Cast<UPlayerAnim>(GetMesh()->GetAnimInstance());
	AnimInst->WeaponType = Type;
}


