// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SaveLoadManager.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJ_API USaveLoadManager : public UObject
{
	GENERATED_BODY()



public:
	void Load(class AMyPlayer* Player);
	void Save(class AMyPlayer* Player);


private:
	
	void LoadPlayerTransform(class AMyPlayer* Player, TSharedPtr<FJsonObject> RObject);
	void LoadPlayerData(class AMyPlayer* Player, TSharedPtr<FJsonObject> RObject);
	void LoadItemData(class AMyPlayer* Player, TSharedPtr<FJsonObject> RObject);
	void LoadSkillData(class AMyPlayer* Player, TSharedPtr<FJsonObject> RObject);
	void LoadQuestData(class AMyPlayer* Player, TSharedPtr<FJsonObject> RObject);

	void SavePlayerTransform(class AMyPlayer* Player, TSharedRef<TJsonWriter<TCHAR>> JWriter);
	void SavePlayerData(class AMyPlayer* Player, TSharedRef<TJsonWriter<TCHAR>> JWriter);
	void SaveItemData(class AMyPlayer* Player, TSharedRef<TJsonWriter<TCHAR>> JWriter);
	void SaveSkillData(class AMyPlayer* Player, TSharedRef<TJsonWriter<TCHAR>> JWriter);
	void SaveQuestData(class AMyPlayer* Player, TSharedRef<TJsonWriter<TCHAR>> JWriter);

};
