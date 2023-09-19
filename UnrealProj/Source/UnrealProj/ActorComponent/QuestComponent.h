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
	void LoadPossibleQuest(struct FQuestData* Data);
	void PossibleToOngoing(struct FQuestData* Data);
		
private:
	TArray<struct FQuestData*> PossibleQuests;
	TArray<struct FQuestData*> OngoingQuests;
};
