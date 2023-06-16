


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
		auto StatData = MyGameInstance->GetPlayerStat(Level);
		{
			if (StatData)
			{
				Level = StatData->Level;
				MaxHp = StatData->MaxHp;
				Hp = StatData->MaxHp;
				Attack = StatData->Attack;
			}
		}
	}
}

void UPlayerStatComponent::OnAttacked(float DamageAmount)
{
	Hp -= DamageAmount;
	if (Hp < 0)
		Hp = 0;
}

