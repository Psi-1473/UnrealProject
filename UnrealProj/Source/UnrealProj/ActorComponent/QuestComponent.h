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
	struct FQuestData* GetPossibleQuestDataByQuestIndex(int Index);
	struct FQuestData* GetPossibleQuestData(int PossibleListIndex);
public:	
	void LoadPossibleQuest(struct FQuestData* Data);
	void PossibleToOngoing(struct FQuestData* Data);
		
private:
	// UPROPERTY ..
	UPROPERTY()
	TArray<int> PossibleQuests;
	UPROPERTY()
	TArray<int> OngoingQuests;
};
