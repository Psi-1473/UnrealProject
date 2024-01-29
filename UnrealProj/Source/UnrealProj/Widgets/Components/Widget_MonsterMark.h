// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widget_MonsterMark.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJ_API UWidget_MonsterMark : public UUserWidget
{
	GENERATED_BODY()

public:
	void PlayAnim();
private:
	UPROPERTY(Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* ShakeUI;
	
};
