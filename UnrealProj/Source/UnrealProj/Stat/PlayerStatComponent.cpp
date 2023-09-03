


#include "PlayerStatComponent.h"
#include "../MyGameInstance.h"
#include "Kismet/GameplayStatics.h"

UPlayerStatComponent::UPlayerStatComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true;

	Level = 1;
}


void UPlayerStatComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

void UPlayerStatComponent::InitializeComponent()
{
	Super::InitializeComponent();

	SetLevel(Level);
}


void UPlayerStatComponent::SetLevel(int32 NewLevel)
{
	auto MyGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	if (MyGameInstance)
	{
		auto StatData = MyGameInstance->GetPlayerStat(NewLevel);
		{
			if (StatData)
			{
				Level = StatData->Level;
				MaxHp = StatData->MaxHp;
				Hp = StatData->MaxHp;
				MaxExp = StatData->MaxExp;
				SetExp(0);
				Attack = StatData->Attack;
				UE_LOG(LogTemp, Warning, TEXT("Level Set : %d"), Level);
			}
		}
	}
}

void UPlayerStatComponent::AddExp(int32 Value)
{
	Exp += Value;
	int ExpToAdd;
	if (Exp >= MaxExp)
	{
		ExpToAdd = Exp - MaxExp;
		SetLevel(Level + 1);
	}
	else ExpToAdd = Exp;

	SetExp(ExpToAdd);
}

void UPlayerStatComponent::SetHp(int32 Value)
{
	Hp = Value;
	if (Hp < 0)
		Hp = 0;

	if (Hp > MaxHp)
		Hp = MaxHp;

	OnHpChanged.Broadcast();
}

void UPlayerStatComponent::SetExp(int32 Value)
{
	Exp = Value;
	// UI 업데이트 
	OnExpChanged.Broadcast();
}

void UPlayerStatComponent::SetMp(int32 Value)
{
	Mp = Value;
	if (Mp < 0)
		Mp = 0;

	OnMpChanged.Broadcast();
}

void UPlayerStatComponent::AddHp(int Value)
{
	SetHp(Hp + Value);
}

void UPlayerStatComponent::AddMp(int Value)
{
	SetMp(Mp + Value);
}

void UPlayerStatComponent::OnAttacked(float DamageAmount)
{
	int32 NewHp = Hp - DamageAmount;
	SetHp(NewHp);
}

