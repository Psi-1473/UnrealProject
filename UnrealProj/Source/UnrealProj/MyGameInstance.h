// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Engine/DataTable.h"
#include "Managers//UIManager.h"
#include "Components/RichTextBlockImageDecorator.h"
#include "MyGameInstance.generated.h"



static UIManager ManagerUI;

USTRUCT()
struct FMyPlayerData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Level;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Attack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxHp;
};
USTRUCT()
struct FMonsterData : public FTableRowBase
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Id;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Level;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Attack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxHp;
};
USTRUCT()
struct FNpcData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Id;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString DefaultLine;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Type;
};

UCLASS()
class UNREALPROJ_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UMyGameInstance();

	FMyPlayerData* GetPlayerStat(int32 Level);
	FMonsterData* GetMonsterStat(FString Name);
	FNpcData* GetNpcData(int32 Id);
	FRichImageRow* GetUseItemImage(int32 Id);

private:
	UPROPERTY()
	class UDataTable* PlayerStats;

	UPROPERTY()
	class UDataTable* MonsterStats;

	UPROPERTY()
	class UDataTable* NpcData;

	UPROPERTY()
	class UDataTable* ItemImages;
};
