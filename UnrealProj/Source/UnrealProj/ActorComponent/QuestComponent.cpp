// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestComponent.h"
#include "../MyGameInstance.h"

UQuestComponent::UQuestComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}


// Called when the game starts
void UQuestComponent::BeginPlay()
{
	Super::BeginPlay();

	
}

void UQuestComponent::LoadPossibleQuest(FQuestData* Data)
{
	UE_LOG(LogTemp, Warning, TEXT("QUEST LOADED!"));
	PossibleQuests.Add(Data);
}

void UQuestComponent::PossibleToOngoing(FQuestData* Data)
{
}

