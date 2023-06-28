// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../DEFINE.h"

/**
 * 
 */
class UNREALPROJ_API UIManager
{
public:
	UIManager();
	~UIManager();

	void TestFunc();
	UUserWidget* PopupUI(UWorld* World, UIType Type);
	void CloseUI(UIType Type);

public:
	int UiNumber = 0;
	TSubclassOf<UUserWidget> WidgetAsset;
	TArray<UUserWidget*> PopupUiArray;
};
