// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widget_SkillSlot.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJ_API UWidget_SkillSlot : public UUserWidget
{
	GENERATED_BODY()
	
private:
	UPROPERTY(meta = (BindWidget))
	class UImage* Img_Skill;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Text_Name;
};
