// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widget_NpcInfo.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJ_API UWidget_NpcInfo : public UUserWidget
{
	GENERATED_BODY()
public:
	UWidget_NpcInfo(const FObjectInitializer& ObjectInitializer);

	void BindNpc(class ANpc* NpcValue);
	void UpdateQuestMark();
private:
	UPROPERTY(meta = (BindWidget))
	class UImage* Img_QuestMark;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Name;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Job;

	UPROPERTY()
	TWeakObjectPtr<class ANpc> Npc;

	UPROPERTY()
	class UTexture2D* PossibleMark;

	UPROPERTY()
	class UTexture2D* CompletableMark;
};
