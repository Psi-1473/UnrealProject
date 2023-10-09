// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractObjManager.h"
#include "../Creatures/Npc/InteractObject.h"
#include "../Creatures/Npc/LootObject.h"

void UInteractObjManager::AddLootObject(ALootObject* Obj)
{
	if (InterObjects.Find(Obj->GetId()) == nullptr)
	{
		FLootObj LootObj;
		LootObj.LootObjs.Add(Obj);
		
		InterObjects.Add(Obj->GetId(), LootObj);
	}
	else
	{
		InterObjects[Obj->GetId()].LootObjs.Add(Obj);
	}
}

void UInteractObjManager::MakeObjVisible(int Id)
{

	for (int i = 0; i < InterObjects[Id].LootObjs.Num(); i++)
	{
		InterObjects[Id].LootObjs[i]->SetOff();
	}
}

void UInteractObjManager::MakeObjInvisible(int Id)
{
	for (int i = 0; i < InterObjects[Id].LootObjs.Num(); i++)
	{
		InterObjects[Id].LootObjs[i]->SetOn();
	}
}
