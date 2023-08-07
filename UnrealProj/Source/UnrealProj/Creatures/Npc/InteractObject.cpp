// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractObject.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "../Player/MyPlayer.h"

AInteractObject::AInteractObject()
{
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	InteractBox = CreateDefaultSubobject<UBoxComponent>(TEXT("InteractBox"));
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));

	Mesh->SetRelativeLocation(FVector(0.f, 0.f, -88.f));
	Mesh->SetRelativeRotation(FRotator(0.f, -90.f, -0.f));

	InteractBox->SetRelativeScale3D(FVector(2.f, 2.f, 2.f));
	InteractBox->SetCollisionProfileName("InteractBox");

	CapsuleComponent->SetCapsuleHalfHeight(88.f);
	CapsuleComponent->SetCapsuleRadius(34.f);

	RootComponent = CapsuleComponent;
	InteractBox->SetupAttachment(RootComponent);
	Mesh->SetupAttachment(RootComponent);

	InteractBox->OnComponentBeginOverlap.AddDynamic(this, &IInteractable::OnOverlapBegin);
	InteractBox->OnComponentEndOverlap.AddDynamic(this, &IInteractable::OnOverlapEnd);
}

void AInteractObject::BeginPlay()
{
	AActor::BeginPlay();
	
}

void AInteractObject::Tick(float DeltaTime)
{
	AActor::Tick(DeltaTime);

}

void AInteractObject::Interact(AMyPlayer* Player)
{
	UE_LOG(LogTemp, Warning, TEXT("Interact with Obj!"));
}

