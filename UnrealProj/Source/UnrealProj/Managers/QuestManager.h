// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "QuestManager.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJ_API UQuestManager : public UObject
{
	GENERATED_BODY()

public:
	void LoadNpcQuest(class ANpc* Npc);

};
