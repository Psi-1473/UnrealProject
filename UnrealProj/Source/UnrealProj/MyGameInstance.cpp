// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"


UMyGameInstance::UMyGameInstance()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> DATA(TEXT("/Script/Engine.DataTable'/Game/08_Data/Player/PlayerStat.PlayerStat'"));
	static ConstructorHelpers::FObjectFinder<UDataTable> MOBDATA(TEXT("/Script/Engine.DataTable'/Game/08_Data/Monster/MonsterStat.MonsterStat'"));
	if (DATA.Succeeded())
		PlayerStats = DATA.Object;

	if (MOBDATA.Succeeded())
		MonsterStats = MOBDATA.Object;
}

FMyPlayerData* UMyGameInstance::GetPlayerStat(int32 Level)
{
	return PlayerStats->FindRow<FMyPlayerData>(*FString::FromInt(Level), TEXT(""));
}

FMonsterData* UMyGameInstance::GetMonsterStat(FString Name)
{
	return MonsterStats->FindRow<FMonsterData>(*Name, TEXT(""));
}
