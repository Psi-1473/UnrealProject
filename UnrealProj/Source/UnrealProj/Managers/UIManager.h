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

	UUserWidget* PopupUI(UWorld* World, UIType Type);
	void CloseUI(UIType Type);
	void SetController(class AController* Controller) { PlayerController = Controller; }

public:
	int UiNumber = 0;
	TSubclassOf<UUserWidget> WidgetAsset;

	UPROPERTY()
	class AController* PlayerController;

	UPROPERTY()
	TArray<UUserWidget*> PopupUiArray;
};
