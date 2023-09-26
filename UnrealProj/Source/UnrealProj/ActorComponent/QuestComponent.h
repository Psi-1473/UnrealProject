// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "QuestComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREALPROJ_API UQuestComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UQuestComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	int GetPossibleQuestNum() { return PossibleQuests.Num(); }
	int GetCompletableQuestNum() { return CompletableQuests.Num(); }

	struct FQuestData* GetQuestInfoByQuestId(int QuestId);
	struct FQuestData* GetPossibleQuestDataByQuestIndex(int Index);
	struct FQuestData* GetPossibleQuestData(int PossibleListIndex);

	TArray<class UQuest*> GetCompletableQuests() { return CompletableQuests; }
public:	
	void LoadPossibleQuest(struct FQuestData* Data);

	void RemovePossibleQuest(int QuestIndex) { PossibleQuests.Remove(QuestIndex); }
	void RemoveOngoingQuest(class UQuest* Quest) { OngoingQuests.Remove(Quest); }
	void RemoveCompletableQuest(class UQuest* Quest) { CompletableQuests.Remove(Quest); };

	void AddPossibleQuest(int QuestIndex) { PossibleQuests.Add(QuestIndex); }
	void AddOngoingQuest(class UQuest* Quest) { OngoingQuests.Add(Quest); }
	void AddCompletableQuest(class UQuest* Quest) { CompletableQuests.Add(Quest); }
		
private:
	// UPROPERTY ..
	UPROPERTY()
	TArray<int> PossibleQuests;
	UPROPERTY()
	TArray<class UQuest*> OngoingQuests;
	UPROPERTY()
	TArray<class UQuest*> CompletableQuests;
};
