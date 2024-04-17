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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxMp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxExp;
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Exp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MinGold;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxGold;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 AttackType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<int32> DropEquipments;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<int32> DropUseItems;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<int32> DropMiscItems;
};
USTRUCT()
struct FNpcData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Id;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Job;

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 WeaponType;
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
struct FMiscItemData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Id;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 SellPrice;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Percentage;

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 CoolDown;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Mp;
};

USTRUCT()
struct FQuestData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Id;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 QuestType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 QuestLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 PossibleLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Explanation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 TargetType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 TargetId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 TargetNum;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 QuestNpcId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ClearNpcId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 NextQuestNpcId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 NextQuestId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Summary;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool CanLoad;
};

USTRUCT()
struct FVehicleData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Id;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Explanation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DashSpeed;
};

USTRUCT()
struct FScriptData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 NowPage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 LastPage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Line;
};



UCLASS()
class UNREALPROJ_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UMyGameInstance();

	virtual void Init() override;

	FMyPlayerData* GetPlayerStat(int32 Level);
	FMonsterData* GetMonsterStat(int32 Id);
	FNpcData* GetNpcData(int32 Id);

	/*
		Data with Image
	*/
	FWeaponData* GetSwordData(int32 Id);
	FWeaponData* GetBowData(int32 Id);
	FUseItemData* GetUseItemData(int32 Id);
	FMiscItemData* GetMiscItemData(int32 Id);
	FVehicleData* GetVehicleData(int32 Id);

	FRichImageRow* GetSwordImage(int32 Id);
	FRichImageRow* GetBowImage(int32 Id);
	FRichImageRow* GetUseItemImage(int32 Id);
	FRichImageRow* GetMiscItemImage(int32 Id);
	/*
	
	*/

	FSkillData* GetPlayerSkillData(FString Type, int32 Id);
	FSkillData* GetSwordSkillData(int32 Id);
	FSkillData* GetBowSkillData(int32 Id);

	FQuestData* GetSingleQuestData(int NpcId, int QuestId);

	class UDataTable* GetQuestData(int NpcId);
	class UDataTable* GetQuestScript(int NpcId, int QuestId);

	TSharedPtr<UIManager> GetUIMgr() { return UIMgr; }
	class UScriptManager* GetScriptMgr() { return ScriptMgr; }
	class UResourceManager* GetResourceMgr() { return ResourceMgr; }
	class UPoolManager* GetPoolMgr() { return PoolMgr; }
	class UQuestManager* GetQuestMgr() { return QuestMgr; }
	class UInteractObjManager* GetInterObjMgr() { return InterObjMgr; }
	class USoundManager* GetSoundMgr() { return SoundMgr; }
	class USaveLoadManager* GetSaveLoadMgr() { return SaveLoadMgr; }

public:
	TArray<class ANpc*> GetNpcList() { return NpcList; }

	void AddNpc(int32 Index, class ANpc* Npc) { NpcList[Index] = Npc; }

public:
	void CheckQuest(int QuestType, int TargetId, TWeakObjectPtr<class AMyPlayer> Player, int TargetType = 0);
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
	class UDataTable* MiscItemData;

	UPROPERTY()
	class UDataTable* SwordImages;
	
	UPROPERTY()
	class UDataTable* BowImages;

	UPROPERTY()
	class UDataTable* ItemImages;

	UPROPERTY()
	class UDataTable* MiscImages;

	UPROPERTY()
	class UDataTable* SwordSkillData;

	UPROPERTY()
	class UDataTable* BowSkillData;

	UPROPERTY()
	class UDataTable* VehicleData;
public:

	void AddNpcNumber();
	void InitNpcQuest();
private:
	FString GetQuestScriptDir(int NpcId, int QuestId);
	FString GetQuestDataDir(int NpcId);
private:
	TSharedPtr<UIManager> UIMgr;

	UPROPERTY()
	class UScriptManager* ScriptMgr;

	UPROPERTY()
	class UResourceManager* ResourceMgr;

	UPROPERTY()
	class UPoolManager* PoolMgr;

	UPROPERTY()
	class UQuestManager* QuestMgr;

	UPROPERTY()
	class UInteractObjManager* InterObjMgr;

	UPROPERTY()
	class USoundManager* SoundMgr;

	UPROPERTY()
	class USaveLoadManager* SaveLoadMgr;

private:
	UPROPERTY()
	TArray<class ANpc*> NpcList;
	
	UPROPERTY()
	int32 NpcNumber = 0;
};
