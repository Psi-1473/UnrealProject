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
	RObject->TryGetNumberField(TEXT("Level"), Level);
	RObject->TryGetNumberField(TEXT("Hp"), Hp);
	RObject->TryGetNumberField(TEXT("Mp"), Mp);
	RObject->TryGetNumberField(TEXT("Exp"), Exp);

	Comp->SetLevel(Level);
	Comp->SetHp(Hp);
	Comp->SetMp(Mp);
	Comp->SetExp(Exp);
	
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


}

void USaveLoadManager::LoadSkillData(AMyPlayer* Player, TSharedPtr<FJsonObject> RObject)
{
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
	JWriter->WriteValue(TEXT("Level"), Comp->GetLevel());
	JWriter->WriteValue(TEXT("Attack"), Comp->GetAttack());
	JWriter->WriteValue(TEXT("MaxHp"), Comp->GetMaxHp());
	JWriter->WriteValue(TEXT("MaxMp"), Comp->GetMaxMp());
	JWriter->WriteValue(TEXT("MaxExp"), Comp->GetMaxExp());
	JWriter->WriteValue(TEXT("Hp"), Comp->GetHp());
	JWriter->WriteValue(TEXT("Mp"), Comp->GetMp());
	JWriter->WriteValue(TEXT("Exp"), Comp->GetExp());
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
}

void USaveLoadManager::SaveQuestData(AMyPlayer* Player, TSharedRef<TJsonWriter<TCHAR>> JWriter)
{
}
