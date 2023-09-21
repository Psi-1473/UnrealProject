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
	void BindQuest(struct FQuestData* QuestData);
private:
	UPROPERTY()
	QuestType Type;

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


	

	
};
