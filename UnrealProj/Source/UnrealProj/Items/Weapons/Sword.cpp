// Fill out your copyright notice in the Description page of Project Settings.


#include "Sword.h"
#include "../../Creatures/Player/MyPlayer.h"

void ASword::OnLeftMouseClicked(AMyPlayer* Player)
{
	Super::OnLeftMouseClicked(Player);
	UE_LOG(LogTemp, Warning, TEXT("Sword Left Clicked!"));
}

void ASword::OnRightMouseClicked(AMyPlayer* Player)
{
	Super::OnRightMouseClicked(Player);

	FString Str = FString::FromInt((int)Player->GetWeapon()->GetType());
	UE_LOG(LogTemp, Warning, TEXT("WEAPON IS NOT A BOW : %s"), *Str);
}
