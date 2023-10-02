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
	void BindQuest(class UQuest* Data); // ����Ʈ Ŭ������ ������ �����ͷ� ������ ����
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
	class UQuest* Quest; // �����ͷ� �ٲ� ���� ����

};
