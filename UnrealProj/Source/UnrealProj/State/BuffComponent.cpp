// Fill out your copyright notice in the Description page of Project Settings.


#include "BuffComponent.h"
#include "CharacterState.h"
#include "BuffState.h"
#include "../DEFINE.h"


void UBuffComponent::Init()
{
	UBurnState* BurnState = NewObject<UBurnState>();
	UPoisonState* PoisonState = NewObject<UPoisonState>();

	Debuffs.Add((uint8)EDebuff::Burning, BurnState);
	Debuffs.Add((uint8)EDebuff::Poison, PoisonState);
}

void UBuffComponent::SetDebuff(uint8 Value)
{
	DebuffFlag = DebuffFlag | Value;
	Debuffs[Value]->OnEnter();
}

void UBuffComponent::RemoveDebuff(uint8 Value)
{
	DebuffFlag = DebuffFlag & (~Value);
	Debuffs[Value]->OnExit();

}

void UBuffComponent::UpdateDebuff()
{
	if ((DebuffFlag & (int)EDebuff::Burning) == (int)EDebuff::Burning)
		Debuffs[(int)EDebuff::Burning]->OnUpdate();


	if ((DebuffFlag & (int)EDebuff::Poison) == (int)EDebuff::Poison)
		Debuffs[(int)EDebuff::Poison]->OnUpdate();


}