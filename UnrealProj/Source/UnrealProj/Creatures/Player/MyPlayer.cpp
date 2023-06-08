// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayer.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "../../Animations/Player/PlayerAnim.h"
#include "../../State/StateMachine.h"
#include "../../Weapon.h"
#include "GameFramework/CharacterMovementComponent.h"




AMyPlayer::AMyPlayer()
{
	PrimaryActorTick.bCanEverTick = true;

	AnimClasses.Init(nullptr, WEAPON_END);

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonAurora/Characters/Heroes/Aurora/Meshes/Aurora.Aurora'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> WeaponAsset(TEXT("/Script/Engine.StaticMesh'/Game/04_Mesh/Weapon/Sword1.Sword1'"));
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

	Weapon = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WEAPON"));

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
	
	UWeapon* NewWeapon = NewObject<UWeapon>();
	NewWeapon->Init(WEAPON_ARROW, 0);

	EquipWeapon(NewWeapon);
	

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
	FName WeaponSocket(_Weapon->GetSocketName());
	
	if (GetMesh()->DoesSocketExist(WeaponSocket))
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, TEXT("EQUIP!"));
		EquipedWeapon = _Weapon;
		Weapon->SetStaticMesh(EquipedWeapon->GetStaticMesh());
		Weapon->SetupAttachment(GetMesh(), WeaponSocket);
	}
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

void AMyPlayer::SetAnimByWeapon(WEAPONTYPE Type)
{
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	GetMesh()->SetAnimClass(AnimClasses[Type]);
	AnimInst = Cast<UPlayerAnim>(GetMesh()->GetAnimInstance());
	AnimInst->WeaponType = Type;
}


