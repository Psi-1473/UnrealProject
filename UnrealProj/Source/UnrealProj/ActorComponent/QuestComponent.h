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
	int32 GetMainPossibleNumber() { return MainPossibleNumber; }
	int32 GetMainCompletableNumber() { return MainCompletableNumber; }

	void DecreaseMainCompletableNumber() { MainCompletableNumber--; }

	struct FQuestData* GetQuestInfoByQuestId(int QuestId);
	struct FQuestData* GetPossibleQuestDataByQuestIndex(int Index);
	struct FQuestData* GetPossibleQuestData(int PossibleListIndex);

	TArray<class UQuest*> GetCompletableQuests() { return CompletableQuests; }
public:	
	void LoadPossibleQuest(struct FQuestData* Data);

	void RemovePossibleQuest(int QuestId);
	void RemoveOngoingQuest(class UQuest* Quest);
	void RemoveCompletableQuest(class UQuest* Quest);

	void AddPossibleQuest(int QuestId);
	void AddOngoingQuest(class UQuest* Quest);
	void AddCompletableQuest(class UQuest* Quest);

private:
	bool IsQuestInOnGoing(int Id);
	bool IsQuestInCompletable(int Id);

		
private:

	// UPROPERTY ..
	UPROPERTY()
	int32 MainPossibleNumber;

	UPROPERTY()
	int32 MainCompletableNumber;

	UPROPERTY()
	TArray<int> PossibleQuests;
	UPROPERTY()
	TArray<class UQuest*> OngoingQuests;
	UPROPERTY()
	TArray<class UQuest*> CompletableQuests;
};
