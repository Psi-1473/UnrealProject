// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerSkill_Sword_First.h"
#include "../../../Creatures/Player/MyPlayer.h"
#include "../../../Animations/Player/PlayerAnim.h"
#include "../../EffectActor/SkillEffectActor.h"

UPlayerSkill_Sword_First::UPlayerSkill_Sword_First()
{
	static ConstructorHelpers::FClassFinder<ASkillEffectActor> EFFECT(TEXT("/Script/Engine.Blueprint'/Game/02_Blueprints/SkillEffectActor/Player/0/BP_Effect_0_1.BP_Effect_0_1_C'"));

	if (EFFECT.Succeeded())
		Effect = EFFECT.Class;
}

void UPlayerSkill_Sword_First::Execute(AActor* OwnerActor)
{
	Super::Execute(OwnerActor);
	UE_LOG(LogTemp, Warning, TEXT("SWORD FIRST SKILL"));

	auto OwnerPlayer = Cast<AMyPlayer>(OwnerActor);
	if (OwnerPlayer == nullptr)
		return;
	OwnerPlayer->SetSkill(this);
	OwnerPlayer->GetAnimInst()->PlaySkillMontage(Id);
}

void UPlayerSkill_Sword_First::PlayParticle(AActor* OwnerActor)
{
	auto OwnerPlayer = Cast<AMyPlayer>(OwnerActor);
	if (OwnerPlayer == nullptr)
		return;

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = OwnerPlayer;
	SpawnParams.Instigator = OwnerPlayer->GetInstigator();

	FVector CameraLocation;
	FRotator CameraRotation;
	OwnerPlayer->GetActorEyesViewPoint(CameraLocation, CameraRotation);
	CameraRotation.Pitch += 5.f;

	if (Effect == nullptr)
		return;
	//FString s = FString::FromInt(OwnerPlayer->GetActorLocation().X);
	UE_LOG(LogTemp, Warning, TEXT("STR : %f"), OwnerPlayer->GetActorLocation().X);
	ASkillEffectActor* EffectActor = OwnerPlayer->GetWorld()->SpawnActor<ASkillEffectActor>(Effect,
		OwnerPlayer->GetActorLocation(),
		OwnerPlayer->GetActorRotation(),
		SpawnParams);
}
