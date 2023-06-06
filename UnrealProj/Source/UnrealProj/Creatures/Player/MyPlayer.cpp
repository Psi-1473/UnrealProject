// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayer.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

#include "GameFramework/CharacterMovementComponent.h"




AMyPlayer::AMyPlayer()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("/Script/Engine.SkeletalMesh'/Game/04_Characters/Mannequins/Meshes/SKM_Manny.SKM_Manny'"));
	
	if (MeshAsset.Succeeded())
	{
		GetMesh()->SkeletalMesh = MeshAsset.Object;
		GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -88.f));
		GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, -0.f));
	}

	SetDefaultCamera();
}

void AMyPlayer::BeginPlay()
{
	Super::BeginPlay();
}

void AMyPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMyPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
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


