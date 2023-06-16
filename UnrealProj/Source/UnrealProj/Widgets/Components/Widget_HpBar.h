// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widget_HpBar.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJ_API UWidget_HpBar : public UUserWidget
{
	GENERATED_BODY()
public:
	void BindHp(class UMonsterStatComponent* StatComp);
	void UpdateHp();
	
private:
	UPROPERTY()
	class UMonsterStatComponent* CurrentStatComp;

	UPROPERTY(meta=(BindWidget))
	class UProgressBar* PB_HpBar;
};
