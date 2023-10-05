


#include "PlayerStatComponent.h"
#include "../MyGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "Kismet/GameplayStatics.h"
#include "../Creatures/Player/MyPlayer.h"
#include "../Managers/QuestManager.h"
#include "../Skills/Components/PlayerSkillComponent.h"

UPlayerStatComponent::UPlayerStatComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true;
	Level = 1;
	static ConstructorHelpers::FObjectFinder<UParticleSystem> LevelEffect(TEXT("/Script/Engine.ParticleSystem'/Game/ParagonSparrow/FX/Particles/Sparrow/Abilities/Ultimate/FX/P_Sparrow_UltHitWorld_WaterImpact.P_Sparrow_UltHitWorld_WaterImpact'"));
	if (LevelEffect.Succeeded())
		LevelUpEffect = LevelEffect.Object;
}


void UPlayerStatComponent::BeginPlay()
{
	Super::BeginPlay();
	Level = 1;
}

void UPlayerStatComponent::InitializeComponent()
{
	Super::InitializeComponent();

	SetLevel(1);
}


void UPlayerStatComponent::SetLevel(int32 NewLevel)
{
	auto MyGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	OnLevelChanged.Broadcast();
	if (MyGameInstance)
	{
		auto StatData = MyGameInstance->GetPlayerStat(NewLevel);
		{
			if (StatData)
			{
				Level = StatData->Level;
				MaxHp = StatData->MaxHp;
				Hp = StatData->MaxHp;
				MaxMp = StatData->MaxMp;
				Mp = StatData->MaxMp;
				MaxExp = StatData->MaxExp;
				SetExp(0);
				Attack = StatData->Attack;
				UE_LOG(LogTemp, Warning, TEXT("Level Set : %d"), Level);
				OnLevelChanged.Broadcast();
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
		//TEMP
		auto MyGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
		auto Char = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
		auto MyPlayer = Cast<AMyPlayer>(Char);
		UGameplayStatics::SpawnEmitterAtLocation(MyPlayer->GetWorld(), LevelUpEffect, MyPlayer->GetActorLocation()); //Temp
		SetLevel(Level + 1);
		MyGameInstance->GetQuestMgr()->LoadNpcQuestByLevelUp(MyPlayer);
		MyPlayer->GetSkillComponent()->GainSkillPoint();
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
	// UI ������Ʈ 
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

