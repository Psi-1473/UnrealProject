// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget_Looting.h"
#include "Components/ProgressBar.h"
#include "../../Creatures/Npc/LootObject.h"

void UWidget_Looting::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (GoalTime == 0)
		return;

	float NowTime = (LootObj->GetWorld()->GetTimeSeconds() - PrevTime);

	UE_LOG(LogTemp, Warning, TEXT("Goal : %f, Prev : %f, Now : %f, GetTime : %f"), GoalTime, PrevTime, NowTime, GetWorld()->GetTimeSeconds());
	PB_Bar->SetPercent(NowTime / GoalTime);

	if (NowTime >= GoalTime)
	{
		LootObj->LootEnd();
	}
}

void UWidget_Looting::SetTime(float Value, TWeakObjectPtr<class ALootObject> Obj)
{
	GoalTime = Value;
	LootObj = Obj;
	PrevTime = LootObj->GetWorld()->GetTimeSeconds();
}
