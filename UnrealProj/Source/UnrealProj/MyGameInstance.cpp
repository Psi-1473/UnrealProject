// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"


UMyGameInstance::UMyGameInstance()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> DATA(TEXT("/Script/Engine.DataTable'/Game/08_Data/Player/PlayerStat.PlayerStat'"));
	static ConstructorHelpers::FObjectFinder<UDataTable> MOBDATA(TEXT("/Script/Engine.DataTable'/Game/08_Data/Monster/MonsterStat.MonsterStat'"));
	static ConstructorHelpers::FObjectFinder<UDataTable> ITEMIMAGE(TEXT("/Script/Engine.DataTable'/Game/08_Data/Item/UseItemImage.UseItemImage'"));
	
	if (DATA.Succeeded()) PlayerStats = DATA.Object;
	if (MOBDATA.Succeeded()) MonsterStats = MOBDATA.Object;
	if (ITEMIMAGE.Succeeded()) ItemImages = ITEMIMAGE.Object;
}

FMyPlayerData* UMyGameInstance::GetPlayerStat(int32 Level)
{
	ManagerUI.TestFunc();
	return PlayerStats->FindRow<FMyPlayerData>(*FString::FromInt(Level), TEXT(""));
}

FMonsterData* UMyGameInstance::GetMonsterStat(FString Name)
{
	return MonsterStats->FindRow<FMonsterData>(*Name, TEXT(""));
}

FRichImageRow* UMyGameInstance::GetUseItemImage(int32 Id)
{
	return ItemImages->FindRow<FRichImageRow>(*FString::FromInt(Id), TEXT(""));
}

