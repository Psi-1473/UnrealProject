// Fill out your copyright notice in the Description page of Project Settings.


#include "BuffState.h"

void UBuffState::OnEnter()
{
}

void UBuffState::OnUpdate()
{
}

void UBuffState::OnExit()
{
}

void UBurnState::OnEnter()
{
	UE_LOG(LogTemp, Warning, TEXT(" BURN START "));
}

void UBurnState::OnUpdate()
{
	UE_LOG(LogTemp, Warning, TEXT(" BURNING "));
}

void UBurnState::OnExit()
{
	UE_LOG(LogTemp, Warning, TEXT(" BURN END "));
}

void UPoisonState::OnEnter()
{
	UE_LOG(LogTemp, Warning, TEXT(" POISON START "));
}

void UPoisonState::OnUpdate()
{
	UE_LOG(LogTemp, Warning, TEXT(" POISON !! "));
}

void UPoisonState::OnExit()
{
	UE_LOG(LogTemp, Warning, TEXT(" POISON END "));
}
