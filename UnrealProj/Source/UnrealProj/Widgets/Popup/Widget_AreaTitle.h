// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widget_AreaTitle.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJ_API UWidget_AreaTitle : public UUserWidget
{
	GENERATED_BODY()

public:
	void Init(class AAreaBox* Area);
	void CloseThis();
private:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Name;

	UPROPERTY()
	FTimerHandle DestroyTimer;
};
