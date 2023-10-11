// Fill out your copyright notice in the Description page of Project Settings.


#include "SEA_Bow_Third.h"
#include "../../../Helpers/AttackChecker.h"
#include "Sound/SoundWave.h"
#include "Components/AudioComponent.h"

ASEA_Bow_Third::ASEA_Bow_Third()
{
	static ConstructorHelpers::FObjectFinder<USoundWave> AttackSound(TEXT("/Script/Engine.SoundWave'/Game/10_Sound/Sound/Player/Arrow/Sound_Player_Bow3Thunder.Sound_Player_Bow3Thunder'"));
	if (AttackSound.Succeeded()) Sound_Attack = AttackSound.Object;
}

void ASEA_Bow_Third::BeginPlay()
{
	Super::BeginPlay();

	// 1. õ�� ����Ʈ ����Ʈ��
	// 2. Ÿ�̸� ��� - õ���� �ٴڿ� ���� �� AttackCheck �����ϵ���
	// 3. Ÿ�̸� ��� - �� ������Ʈ�� �ı��ǵ���
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
	AudioComponent->SetSound(Sound_Attack);
	AudioComponent->Play();
	TArray<FOverlapResult> Mobs;
	Mobs = UAttackChecker::PlayerCircleCheck(GetActorLocation(), 500.f, 500.f, ECC_GameTraceChannel5, this);
	UAttackChecker::ApplyOverlapDamageToActors(20.f, GetOwner(), Mobs);
}
