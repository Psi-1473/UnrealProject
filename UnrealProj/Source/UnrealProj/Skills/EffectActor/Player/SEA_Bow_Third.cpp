// Fill out your copyright notice in the Description page of Project Settings.


#include "SEA_Bow_Third.h"
#include "../../../Helpers/AttackChecker.h"

ASEA_Bow_Third::ASEA_Bow_Third()
{
}

void ASEA_Bow_Third::BeginPlay()
{
	Super::BeginPlay();

	// 1. 천둥 이펙트 떨어트림
	// 2. 타이머 등록 - 천둥이 바닥에 닿을 때 AttackCheck 실행하도록
	// 3. 타이머 등록 - 이 오브젝트가 파괴되도록
	AttackCheck();
	FTimerDelegate TimeCallback;
	TimeCallback.BindLambda([this] {
		this->Destroy();
		GetWorldTimerManager().ClearTimer(DestroyTimerHandle);
		});
	GetWorldTimerManager().SetTimer(DestroyTimerHandle, TimeCallback, 1.f, false);
}

void ASEA_Bow_Third::AttackCheck()
{
	UE_LOG(LogTemp, Warning, TEXT("Attack Check"));
	TArray<FOverlapResult> Mobs;
	Mobs = UAttackChecker::PlayerCircleCheck(GetActorLocation(), 500.f, 500.f, ECC_GameTraceChannel5, this);
	UAttackChecker::ApplyOverlapDamageToActors(20.f, GetOwner(), Mobs);
}
