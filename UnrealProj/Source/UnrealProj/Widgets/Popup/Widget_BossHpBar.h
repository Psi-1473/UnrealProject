// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widget_BossHpBar.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJ_API UWidget_BossHpBar : public UUserWidget
{
	GENERATED_BODY()
	

private:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Name;

	UPROPERTY(meta = (BindWidget))
	class UProgressBar* PB_Hp;
};
