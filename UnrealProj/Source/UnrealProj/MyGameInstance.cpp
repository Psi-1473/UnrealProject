// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"
#include "Managers/ScriptManager.h"
#include "Managers/QuestManager.h"


UMyGameInstance::UMyGameInstance()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> DATA(TEXT("/Script/Engine.DataTable'/Game/08_Data/Player/PlayerStat.PlayerStat'"));
	static ConstructorHelpers::FObjectFinder<UDataTable> MOBDATA(TEXT("/Script/Engine.DataTable'/Game/08_Data/Monster/MonsterStat.MonsterStat'"));
	static ConstructorHelpers::FObjectFinder<UDataTable> UseImage(TEXT("/Script/Engine.DataTable'/Game/08_Data/Item/UseItemImage.UseItemImage'"));
	static ConstructorHelpers::FObjectFinder<UDataTable> NPC(TEXT("/Script/Engine.DataTable'/Game/08_Data/Npc/NpcDataTable.NpcDataTable'"));
	static ConstructorHelpers::FObjectFinder<UDataTable> Sword(TEXT("/Script/Engine.DataTable'/Game/08_Data/Weapon/SwordData.SwordData'"));
	static ConstructorHelpers::FObjectFinder<UDataTable> Bow(TEXT("/Script/Engine.DataTable'/Game/08_Data/Weapon/BowData.BowData'"));
	static ConstructorHelpers::FObjectFinder<UDataTable> UseItem(TEXT("/Script/Engine.DataTable'/Game/08_Data/Item/UseItemData.UseItemData'"));
	static ConstructorHelpers::FObjectFinder<UDataTable> SwordImage(TEXT("/Script/Engine.DataTable'/Game/08_Data/Weapon/Image/SwordImageTable.SwordImageTable'"));
	static ConstructorHelpers::FObjectFinder<UDataTable> BowImage(TEXT("/Script/Engine.DataTable'/Game/08_Data/Weapon/Image/BowImageTable.BowImageTable'"));
	static ConstructorHelpers::FObjectFinder<UDataTable> SwordSkill(TEXT("/Script/Engine.DataTable'/Game/08_Data/Player/Skill/SwordSkillData.SwordSkillData'"));
	static ConstructorHelpers::FObjectFinder<UDataTable> BowSkill(TEXT("/Script/Engine.DataTable'/Game/08_Data/Player/Skill/BowSkillData.BowSkillData'"));
	
	if (DATA.Succeeded()) PlayerStats = DATA.Object;
	if (MOBDATA.Succeeded()) MonsterStats = MOBDATA.Object;
	if (UseImage.Succeeded()) ItemImages = UseImage.Object;
	if (NPC.Succeeded()) NpcData = NPC.Object;
	if (Sword.Succeeded()) SwordData = Sword.Object;
	if (Bow.Succeeded()) BowData = Bow.Object;
	if (UseItem.Succeeded()) UseItemData = UseItem.Object;
	if (SwordImage.Succeeded()) SwordImages = SwordImage.Object;
	if (BowImage.Succeeded()) BowImages = BowImage.Object;
	if (SwordSkill.Succeeded()) SwordSkillData = SwordSkill.Object;
	if (BowSkill.Succeeded()) BowSkillData = BowSkill.Object;

	UIMgr = MakeShared<UIManager>();

	ScriptMgr = NewObject<UScriptManager>();
	QuestMgr = NewObject<UQuestManager>();
}

FMyPlayerData* UMyGameInstance::GetPlayerStat(int32 Level)
{
	return PlayerStats->FindRow<FMyPlayerData>(*FString::FromInt(Level), TEXT(""));
}

FMonsterData* UMyGameInstance::GetMonsterStat(FString Name)
{
	return MonsterStats->FindRow<FMonsterData>(*Name, TEXT(""));
}

FNpcData* UMyGameInstance::GetNpcData(int32 Id)
{
	return NpcData->FindRow<FNpcData>(*FString::FromInt(Id), TEXT(""));
}

FWeaponData* UMyGameInstance::GetSwordData(int32 Id)
{
	return SwordData->FindRow<FWeaponData>(*FString::FromInt(Id), TEXT(""));
}

FWeaponData* UMyGameInstance::GetBowData(int32 Id)
{
	
	return BowData->FindRow<FWeaponData>(*FString::FromInt(Id), TEXT(""));
}

FUseItemData* UMyGameInstance::GetUseItemData(int32 Id)
{
	return UseItemData->FindRow<FUseItemData>(*FString::FromInt(Id), TEXT(""));
}

FRichImageRow* UMyGameInstance::GetSwordImage(int32 Id)
{
	return SwordImages->FindRow<FRichImageRow>(*FString::FromInt(Id), TEXT(""));
}

FRichImageRow* UMyGameInstance::GetBowImage(int32 Id)
{
	return BowImages->FindRow<FRichImageRow>(*FString::FromInt(Id), TEXT(""));
}

FRichImageRow* UMyGameInstance::GetUseItemImage(int32 Id)
{
	return ItemImages->FindRow<FRichImageRow>(*FString::FromInt(Id), TEXT(""));
}

FSkillData* UMyGameInstance::GetPlayerSkillDate(FString Type, int32 Id)
{
	if (Type == TEXT("Sword"))
		return GetSwordSkillData(Id);

	if (Type == TEXT("Bow"))
		return GetBowSkillData(Id);


	return nullptr;
}

FSkillData* UMyGameInstance::GetSwordSkillData(int32 Id)
{
	return SwordSkillData->FindRow<FSkillData>(*FString::FromInt(Id), TEXT(""));
}

FSkillData* UMyGameInstance::GetBowSkillData(int32 Id)
{
	return BowSkillData->FindRow<FSkillData>(*FString::FromInt(Id), TEXT(""));
}

FQuestData* UMyGameInstance::GetSingleQuestData(int NpcId, int QuestId)
{
	return GetQuestData(NpcId)->FindRow<FQuestData>(*FString::FromInt(QuestId), TEXT(""));
}

UDataTable* UMyGameInstance::GetQuestData(int NpcId)
{
	UDataTable* DataTable = LoadObject<UDataTable>(NULL, *GetQuestDataDir(NpcId), NULL, LOAD_None, NULL);

	return DataTable;
}

FString UMyGameInstance::GetQuestScript(int NpcId, int QuestId, int Page)
{
	//
	UDataTable* DataTable = LoadObject<UDataTable>(NULL, *GetQuestScriptDir(NpcId, QuestId), NULL, LOAD_None, NULL);
	int LastPage = DataTable->FindRow<FScriptData>(*FString::FromInt(1), TEXT(""))->LastPage;

	if (Page > LastPage)
		return TEXT("SCRIPT END");

	FScriptData* ScriptData = DataTable->FindRow<FScriptData>(*FString::FromInt(Page), TEXT(""));
	return ScriptData->Line;
}

FString UMyGameInstance::GetQuestScriptDir(int NpcId, int QuestId)
{
	
	FString NpcStr = FString::FromInt(NpcId);
	FString QuestStr = FString::FromInt(QuestId);
	FString Dir = TEXT("/Script/Engine.DataTable'/Game/08_Data/Script/");
	Dir += NpcId + TEXT("/Quest/") + QuestStr + TEXT(".") + QuestStr + TEXT("'");

	return Dir;
}

FString UMyGameInstance::GetQuestDataDir(int NpcId)
{
	FString NpcStr = FString::FromInt(NpcId);
	FString Dir = TEXT("/Script/Engine.DataTable'/Game/08_Data/Quest/");
	Dir += NpcStr + TEXT(".") + NpcStr + TEXT("'");

	return Dir;
}

