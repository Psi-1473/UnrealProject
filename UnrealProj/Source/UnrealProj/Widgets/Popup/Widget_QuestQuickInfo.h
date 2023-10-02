// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widget_QuestQuickInfo.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJ_API UWidget_QuestQuickInfo : public UUserWidget
{
	GENERATED_BODY()
	
public:
	class UQuest* GetQuest() { return Quest; }
public:
	void BindQuest(class UQuest* Data); // 퀘스트 클래스로 받을지 데이터로 받을지 ㄱㄷ
	void RefreshNumber();
private:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Title;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_NowNum;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_MaxNum;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_MissionObject;

	UPROPERTY(meta = (BindWidget))
	class UButton* Btn_Remove;


	UPROPERTY()
	class UQuest* Quest; // 데이터로 바꿀 수도 있음

};
