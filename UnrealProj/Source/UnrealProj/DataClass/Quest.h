// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "../DEFINE.h"
#include "Quest.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJ_API UQuest : public UObject
{
	GENERATED_BODY()

public:
	class ANpc* GetStartNpc() { return StartNpc; }
	class ANpc* GetClearNpc() { return ClearNpc; }
	FString GetQuestName() { return Name; }
	FString GetQuestExplanation() { return Explanation; }

	int32 GetQuestId() { return QuestId; }
	int32 GetNpcId() { return NpcId; }
	int32 GetNextNpcId() { return NextNpcId; }
	int32 GetNextQuestId() { return NextQuestId; }

public:
	void BindQuest(class UMyGameInstance* GInstance, struct FQuestData* QuestData);
private:
	UPROPERTY()
	int32 Type;

	UPROPERTY()
	int32 QuestLevel;

	UPROPERTY()
	int32 NpcId;

	UPROPERTY()
	int32 QuestId;

	UPROPERTY()
	FString Name;
	
	UPROPERTY()
	FString Explanation;

	UPROPERTY()
	int32 TargetId;

	UPROPERTY()
	int32 TargetMaxNum;

	UPROPERTY()
	int32 TargetNowNum;

	UPROPERTY()
		int32 NextNpcId;

	UPROPERTY()
		int32 NextQuestId;
	UPROPERTY()
	class ANpc* StartNpc;

	UPROPERTY()
	class ANpc* ClearNpc;

	

	
};
