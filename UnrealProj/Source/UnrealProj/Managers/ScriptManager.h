// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ScriptManager.generated.h"

/**
 * 
 */

UCLASS()
class UNREALPROJ_API UScriptManager : public UObject
{
	GENERATED_BODY()
	
public:
	void SetGInstance(class UMyGameInstance* Instance) { GInstance = Instance; }
private:
	FString GetQuestScript(int NpcId, int QuestId, int Page);

private:
	UPROPERTY()
	TWeakObjectPtr<class UMyGameInstance> GInstance;
	
};
