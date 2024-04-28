// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveLoadManager.h"
#include "../Creatures/Player/MyPlayer.h"
#include "../Stat/PlayerStatComponent.h"
#include "../Skills/Components/PlayerSkillComponent.h"
#include "../Inventory/Inventory.h"
#include "../Inventory/EquipItemComponent.h"
#include "../Items/Item.h"
#include "../DEFINE.h"
#include "../Items/Weapons/Weapon.h"
#include "../Items/UseItem/UseItem.h"
#include "../Items/MiscItem/MiscItem.h"
#include "Kismet/GameplayStatics.h"
#include "../MyGameMode.h"
#include "../Widgets/Widget_PlayerMain.h"
#include "../Widgets/Widget_ItemQuick.h"
#include "../Widgets/Widget_SkillQuick.h"
#include "../Skills/Components/PlayerSkillComponent.h"
#include "../Skills/Player/PlayerSkill.h"


void USaveLoadManager::Load(AMyPlayer* Player)
{
	FString FileStr;
	FString FilePath = FPaths::ProjectDir() + TEXT("SaveFiles/test.json");
	FFileHelper::LoadFileToString(FileStr, *FilePath);

	if(FileStr.IsEmpty()) return;

	TSharedRef<TJsonReader<TCHAR>> jsonReader = TJsonReaderFactory<TCHAR>::Create(FileStr);
	TSharedPtr<FJsonObject> jsonObj = MakeShareable(new FJsonObject());

	if (FJsonSerializer::Deserialize(jsonReader, jsonObj) && jsonObj.IsValid())
	{
		FString Name;
		jsonObj->TryGetStringField(TEXT("Name"), Name);
		UE_LOG(LogTemp, Warning, TEXT("Load Test : %s"), *Name);
	}

	LoadPlayerTransform(Player, jsonObj);
	LoadPlayerData(Player, jsonObj);
	LoadItemData(Player, jsonObj);
	LoadSkillData(Player, jsonObj);
	LoadQuestData(Player, jsonObj);
}

void USaveLoadManager::Save(AMyPlayer* Player)
{
	FString FileStr;
	FString FilePath = FPaths::ProjectDir() + TEXT("SaveFiles/test.json");
	TSharedRef<TJsonWriter<TCHAR>> Writer = TJsonWriterFactory<>::Create(&FileStr);

	Writer->WriteObjectStart();
	Writer->WriteValue(TEXT("Name"), TEXT("hi"));

	SavePlayerData(Player, Writer);
	SavePlayerData(Player, Writer);
	SaveItemData(Player, Writer);
	SaveSkillData(Player, Writer);
	SaveQuestData(Player, Writer);

	Writer->WriteObjectEnd();
	Writer->Close();
	FFileHelper::SaveStringToFile(*FileStr, *FilePath);

	UE_LOG(LogTemp, Warning, TEXT("Save : %s"), *FilePath);

	
}

void USaveLoadManager::LoadPlayerTransform(AMyPlayer* Player, TSharedPtr<FJsonObject> RObject)
{
	
}

void USaveLoadManager::LoadPlayerData(AMyPlayer* Player, TSharedPtr<FJsonObject> RObject)
{
	auto Comp = Player->GetStatComponent();
	int32 Level;
	int32 Hp;
	int32 Mp;
	int32 Exp;
	int LocX, LocY, LocZ;
	double RotZ;
	RObject->TryGetNumberField(TEXT("Level"), Level);
	RObject->TryGetNumberField(TEXT("Hp"), Hp);
	RObject->TryGetNumberField(TEXT("Mp"), Mp);
	RObject->TryGetNumberField(TEXT("Exp"), Exp);

	RObject->TryGetNumberField(TEXT("LocX"), LocX);
	RObject->TryGetNumberField(TEXT("LocY"), LocY);
	RObject->TryGetNumberField(TEXT("LocZ"), LocZ);
	RObject->TryGetNumberField(TEXT("Yaw"), RotZ);

	Comp->SetLevel(Level);
	Comp->SetHp(Hp);
	Comp->SetMp(Mp);
	Comp->SetExp(Exp);
	
	FQuat Quat;
	Player->GetController()->SetControlRotation((FRotator(0.f, RotZ, 0.f)));
	//Player->SetActorRotation(FQuat(FRotator(0.f, RotZ, 0.f)));
	Player->SetActorLocation(FVector(LocX, LocY, LocZ));
}

void USaveLoadManager::LoadItemData(AMyPlayer* Player, TSharedPtr<FJsonObject> RObject)
{
	auto Inven = Player->GetInventory();
	auto MyMode = Cast<AMyGameMode>(UGameplayStatics::GetGameMode(Player->GetWorld()));
	auto MainWidget = Cast<UWidget_PlayerMain>(MyMode->GetCurrentWidget());


	const TArray<TSharedPtr<FJsonValue>>* EquipItems;
	if (RObject->TryGetArrayField(TEXT("EquipItems"), EquipItems))
	{
		for (int i = 0; i < EquipItems->Num(); i++)
		{
			TSharedPtr<FJsonObject> jsonItem = (*EquipItems)[i]->AsObject();
			int WeaponType;
			int Id;
			int SlotIndex;
			ItemType IType;

			jsonItem->TryGetNumberField(TEXT("WeaponType"), WeaponType);
			jsonItem->TryGetNumberField(TEXT("Id"), Id);
			jsonItem->TryGetNumberField(TEXT("SlotIndex"), SlotIndex);

			switch (WeaponType)
			{
			case (int)WEAPONTYPE::WEAPON_SWORD:
				IType = ITEM_SWORD;
				break;
			case (int)WEAPONTYPE::WEAPON_BOW:
				IType = ITEM_BOW;
				break;
			default:
				break;
			}

			Inven->GainNewItem(IType, Id, SlotIndex);
		}
	}

	const TArray<TSharedPtr<FJsonValue>>* UseItems;
	if (RObject->TryGetArrayField(TEXT("UseItems"), UseItems))
	{
		for (int i = 0; i < UseItems->Num(); i++)
		{
			TSharedPtr<FJsonObject> jsonItem = (*UseItems)[i]->AsObject();
			int Id;
			int SlotIndex;
			int QuickSlotIndex;
			int Number;

			jsonItem->TryGetNumberField(TEXT("Id"), Id);
			jsonItem->TryGetNumberField(TEXT("SlotIndex"), SlotIndex);
			jsonItem->TryGetNumberField(TEXT("QuickSlotIndex"), QuickSlotIndex);
			jsonItem->TryGetNumberField(TEXT("Number"), Number);

			auto NewItem = Inven->GainNewItem(ITEM_USE, Id, SlotIndex, Number);
			NewItem->SetQuickSlotIndex(QuickSlotIndex);

			if(QuickSlotIndex != -1)
				MainWidget->SetQuickSlotItem(NewItem, QuickSlotIndex);
		}
	}

	const TArray<TSharedPtr<FJsonValue>>* MiscItems;
	if (RObject->TryGetArrayField(TEXT("MiscItems"), MiscItems))
	{
		for (int i = 0; i < UseItems->Num(); i++)
		{
			TSharedPtr<FJsonObject> jsonItem = (*MiscItems)[i]->AsObject();
			int Id;
			int SlotIndex;
			int Number;

			jsonItem->TryGetNumberField(TEXT("Id"), Id);
			jsonItem->TryGetNumberField(TEXT("SlotIndex"), SlotIndex);
			jsonItem->TryGetNumberField(TEXT("Number"), Number);

			auto NewItem = Inven->GainNewItem(ITEM_MISC, Id, SlotIndex, Number);

		}
	}



}

void USaveLoadManager::LoadSkillData(AMyPlayer* Player, TSharedPtr<FJsonObject> RObject)
{
	auto SkillComp = Player->GetSkillComponent();
	auto MyMode = Cast<AMyGameMode>(UGameplayStatics::GetGameMode(Player->GetWorld()));
	auto MainWidget = Cast<UWidget_PlayerMain>(MyMode->GetCurrentWidget());
	int32 SkillPoint;
	RObject->TryGetNumberField(TEXT("SkillPoint"), SkillPoint);
	SkillComp->SkillPoint = SkillPoint;
	const TArray<TSharedPtr<FJsonValue>>* SwordSkills;
	if (RObject->TryGetArrayField(TEXT("SwordSkills"), SwordSkills))
	{
		for (int i = 0; i < SwordSkills->Num(); i++)
		{
			TSharedPtr<FJsonObject> jsonItem = (*SwordSkills)[i]->AsObject();
			int WeaponType;
			int SkillLevel;
			int RegisteredKey;

			jsonItem->TryGetNumberField(TEXT("WeaponType"), WeaponType);
			jsonItem->TryGetNumberField(TEXT("SkillLevel"), SkillLevel);
			jsonItem->TryGetNumberField(TEXT("RegisteredKey"), RegisteredKey);

			auto Skill = SkillComp->SwordSkills[i + 1];
			Skill->SetLevel(SkillLevel);
			if (RegisteredKey != KEY_NONE)
			{
				MainWidget->SkillQuickSlots[RegisteredKey]->SetSkill(Skill);
				SkillComp->RegisterSkill(RegisteredKey, Skill);
			}
		}
	}

	const TArray<TSharedPtr<FJsonValue>>* BowSkills;
	if (RObject->TryGetArrayField(TEXT("BowSkills"), BowSkills))
	{
		for (int i = 0; i < BowSkills->Num(); i++)
		{
			TSharedPtr<FJsonObject> jsonItem = (*BowSkills)[i]->AsObject();
			int WeaponType;
			int SkillLevel;
			int RegisteredKey;

			jsonItem->TryGetNumberField(TEXT("WeaponType"), WeaponType);
			jsonItem->TryGetNumberField(TEXT("SkillLevel"), SkillLevel);
			jsonItem->TryGetNumberField(TEXT("RegisteredKey"), RegisteredKey);

			auto Skill = SkillComp->BowSkills[i + 1];
			Skill->SetLevel(SkillLevel);
			if (RegisteredKey != KEY_NONE)
			{
				MainWidget->SkillQuickSlots[RegisteredKey]->SetSkill(Skill);
				SkillComp->RegisterSkill(RegisteredKey, Skill);
			}
		}
	}
}

void USaveLoadManager::LoadQuestData(AMyPlayer* Player, TSharedPtr<FJsonObject> RObject)
{

}

void USaveLoadManager::SavePlayerTransform(AMyPlayer* Player, TSharedRef<TJsonWriter<TCHAR>> JWriter)
{
	//auto Trans = Player->GetActorTransform();
	//int PosX, PosY, PosZ;
	//int RotX, RotY, RotZ;

	
}

void USaveLoadManager::SavePlayerData(AMyPlayer* Player, TSharedRef<TJsonWriter<TCHAR>> JWriter)
{
	auto Comp = Player->GetStatComponent();
	auto Trans = Player->GetActorTransform();
	JWriter->WriteValue(TEXT("Level"), Comp->GetLevel());
	JWriter->WriteValue(TEXT("Attack"), Comp->GetAttack());
	JWriter->WriteValue(TEXT("MaxHp"), Comp->GetMaxHp());
	JWriter->WriteValue(TEXT("MaxMp"), Comp->GetMaxMp());
	JWriter->WriteValue(TEXT("MaxExp"), Comp->GetMaxExp());
	JWriter->WriteValue(TEXT("Hp"), Comp->GetHp());
	JWriter->WriteValue(TEXT("Mp"), Comp->GetMp());
	JWriter->WriteValue(TEXT("Exp"), Comp->GetExp());
	JWriter->WriteValue(TEXT("LocX"), Player->GetActorLocation().X);
	JWriter->WriteValue(TEXT("LocY"), Player->GetActorLocation().Y);
	JWriter->WriteValue(TEXT("LocZ"), Player->GetActorLocation().Z);
	JWriter->WriteValue(TEXT("Yaw"), Player->GetActorRotation().Yaw);
}

void USaveLoadManager::SaveItemData(AMyPlayer* Player, TSharedRef<TJsonWriter<TCHAR>> JWriter)
{
	auto Inven = Player->GetInventory();
	JWriter->WriteArrayStart(TEXT("EquipItems"));
	for(auto& Item : Inven->GetWeaponItems())
	{
		if(Item == nullptr) continue;
		JWriter->WriteObjectStart();
		auto Weapon = Cast<AWeapon>(Item);
		int WeaponType = static_cast<int>(Weapon->GetType());
		JWriter->WriteValue(TEXT("WeaponType"), WeaponType);
		JWriter->WriteValue(TEXT("Id"), Item->GetId());
		JWriter->WriteValue(TEXT("SlotIndex"), Item->GetSlotIndex());
		JWriter->WriteObjectEnd();
	}
	JWriter->WriteArrayEnd();

	JWriter->WriteArrayStart(TEXT("UseItems"));
	for (auto Item : Inven->GetUseItems())
	{
		if (Item == nullptr) continue;
		JWriter->WriteObjectStart();
		JWriter->WriteValue(TEXT("Id"), Item->GetId());
		JWriter->WriteValue(TEXT("SlotIndex"), Item->GetSlotIndex());
		JWriter->WriteValue(TEXT("QuickSlotIndex"), Item->GetQuickSlotIndex());
		JWriter->WriteValue(TEXT("Number"), Item->GetCount());
		JWriter->WriteObjectEnd();
	}
	JWriter->WriteArrayEnd();

	JWriter->WriteArrayStart(TEXT("MiscItems"));
	for (auto Item : Inven->GetMiscItems())
	{
		if (Item == nullptr) continue;
		JWriter->WriteObjectStart();
		JWriter->WriteValue(TEXT("Id"), Item->GetId());
		JWriter->WriteValue(TEXT("SlotIndex"), Item->GetSlotIndex());
		JWriter->WriteValue(TEXT("Number"), Item->GetCount());
		JWriter->WriteObjectEnd();
	}
	JWriter->WriteArrayEnd();
}

void USaveLoadManager::SaveSkillData(AMyPlayer* Player, TSharedRef<TJsonWriter<TCHAR>> JWriter)
{
	//TODO 1) 배운 스킬 불러오기
	//TODO 2) 스킬 레벨 정보
	//TODO 3) 퀵슬롯에 등록된 스킬
	auto SkillComp = Player->GetSkillComponent();
	int32 SkillPoint = SkillComp->GetSkillPoint();
	JWriter->WriteValue(TEXT("SkillPoint"), SkillPoint);

	JWriter->WriteArrayStart(TEXT("SwordSkills"));
	for (auto& Skill : SkillComp->SwordSkills)
	{
		if (Skill == nullptr) continue;
		JWriter->WriteObjectStart();
		int WeaponType = static_cast<int>(Skill->GetWeaponType());
		JWriter->WriteValue(TEXT("WeaponType"), WeaponType);
		JWriter->WriteValue(TEXT("SkillLevel"), Skill->GetLevel());
		JWriter->WriteValue(TEXT("RegisteredKey"), Skill->GetRegisteredKey());
		JWriter->WriteObjectEnd();
	}
	JWriter->WriteArrayEnd();


	JWriter->WriteArrayStart(TEXT("BowSkills"));
	for (auto& Skill : SkillComp->BowSkills)
	{
		if (Skill == nullptr) continue;
		JWriter->WriteObjectStart();
		int WeaponType = static_cast<int>(Skill->GetWeaponType());
		JWriter->WriteValue(TEXT("WeaponType"), WeaponType);
		JWriter->WriteValue(TEXT("SkillLevel"), Skill->GetLevel());
		JWriter->WriteValue(TEXT("RegisteredKey"), Skill->GetRegisteredKey());
		JWriter->WriteObjectEnd();
	}
	JWriter->WriteArrayEnd();
}

void USaveLoadManager::SaveQuestData(AMyPlayer* Player, TSharedRef<TJsonWriter<TCHAR>> JWriter)
{
}
