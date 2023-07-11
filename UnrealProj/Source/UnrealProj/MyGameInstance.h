// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Engine/DataTable.h"
#include "Managers//UIManager.h"
#include "Components/RichTextBlockImageDecorator.h"
#include "MyGameInstance.generated.h"



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

USTRUCT()
struct FWeaponData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Id;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Price;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Explanation;
};

USTRUCT()
struct FUseItemData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Id;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Amount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Price;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Explanation;
};

USTRUCT()
struct FSkillData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Id;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Explanation;
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
	FWeaponData* GetSwordData(int32 Id);
	FWeaponData* GetBowData(int32 Id);
	FUseItemData* GetUseItemData(int32 Id);
	FRichImageRow* GetSwordImage(int32 Id);
	FRichImageRow* GetBowImage(int32 Id);
	FRichImageRow* GetUseItemImage(int32 Id);
	FSkillData* GetSwordSkillData(int32 Id);
	FSkillData* GetBowSkillData(int32 Id);

	TSharedPtr<UIManager> GetUIMgr() { return UIMgr; }

private:
	UPROPERTY()
	class UDataTable* PlayerStats;

	UPROPERTY()
	class UDataTable* MonsterStats;

	UPROPERTY()
	class UDataTable* NpcData;
	
	UPROPERTY()
	class UDataTable* SwordData;
	
	UPROPERTY()
	class UDataTable* BowData;

	UPROPERTY()
	class UDataTable* UseItemData;

	UPROPERTY()
	class UDataTable* SwordImages;
	
	UPROPERTY()
	class UDataTable* BowImages;

	UPROPERTY()
	class UDataTable* ItemImages;

	UPROPERTY()
	class UDataTable* SwordSkillData;

	UPROPERTY()
	class UDataTable* BowSkillData;

private:
	TSharedPtr<UIManager> UIMgr;
};
