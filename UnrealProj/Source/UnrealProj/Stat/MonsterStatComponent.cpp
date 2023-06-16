// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterStatComponent.h"
#include "../MyGameInstance.h"
#include "../Creatures/Monster/Monster.h"
#include "Kismet/GameplayStatics.h"

UMonsterStatComponent::UMonsterStatComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true;
}


void UMonsterStatComponent::BeginPlay()
{
	Super::BeginPlay();

	
}

void UMonsterStatComponent::InitializeComponent()
{
	auto Owner = Cast<AMonster>(GetOwner());
	if (Owner == nullptr)
		return;

	SetInfo(Owner->GetObjectName());
}

void UMonsterStatComponent::SetInfo(FString NameInfo)
{
	auto MyGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	if (MyGameInstance)
	{
		auto StatData = MyGameInstance->GetMonsterStat(NameInfo);
		{
			if (StatData)
			{
				Name = StatData->Name;
				Id = StatData->Id;
				Level = StatData->Level;
				MaxHp = StatData->MaxHp;
				SetHp(MaxHp);
				Attack = StatData->Attack;
			}
		}
	}
}

void UMonsterStatComponent::SetHp(int32 NewHp)
{
	Hp = NewHp;
	if (Hp < 0)
		Hp = 0;

	OnHpChanged.Broadcast();
}

void UMonsterStatComponent::OnAttacked(float Damage)
{
	int32 NewHp = Hp - Damage;
	SetHp(NewHp);
}



