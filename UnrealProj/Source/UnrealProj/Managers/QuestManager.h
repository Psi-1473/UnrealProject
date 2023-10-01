// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "QuestManager.generated.h"

/**
 * 
 */
USTRUCT()
struct FQuestList
{
	GENERATED_BODY()
public:
	TArray<int> QuestIds;
};
UCLASS()
class UNREALPROJ_API UQuestManager : public UObject
{
	GENERATED_BODY()

public:
	void LoadNpcQuest(class ANpc* Npc, class AMyPlayer* Player);
	void LoadNpcQuest(class ANpc* Npc, int QuestId);
	void LoadNpcQuestByLevelUp(class AMyPlayer* Player);

	void CheckQuestTarget(int QuestType, int TargetId, TWeakObjectPtr<class AMyPlayer> Player, int TargetType = 0);

	void InitCompletedList(int NpcNum);
	void AddToCompletedList(int NpcId, int QuestId);

	void BindQuickWindow(class AMyPlayer* Player, class UQuest* Quest);

	void SetQuestWindow(class UWidget_QuestWindow* Window) {QuestQuickWindow = Window;}
	class UWidget_QuestWindow* GetQuestWindow() {return QuestQuickWindow;}

private:
	UPROPERTY()
	TArray<FQuestList> CompletedQuestList;// 이거 UPROPERTY 안되나?

	UPROPERTY()
	class UWidget_QuestWindow* QuestQuickWindow;

};
