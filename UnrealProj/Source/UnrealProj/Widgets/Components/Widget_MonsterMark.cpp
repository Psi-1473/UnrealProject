// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget_MonsterMark.h"
#include "Animation/WidgetAnimation.h"

void UWidget_MonsterMark::PlayAnim()
{
	StopAllAnimations();
	if (IsValid(ShakeUI))
	{
		PlayAnimation(ShakeUI);
		UE_LOG(LogTemp, Warning, TEXT("Start Anim"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Null Start"));
	}
}
