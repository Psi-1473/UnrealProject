// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


const int8 MAX_Inventory = 18;


UENUM(BlueprintType)
enum class UIType : uint8
{
	Inventory,

	End,
};

UENUM(BlueprintType)
enum class STATE : uint8
{
	IDLE,
	MOVE,
	JUMP,
	ATTACK,
	SKILL,
	SKILLCAST,
};

enum InventoryType
{
	Equip,
	Use,
	Etc,
};

enum WEAPONTYPE
{
	WEAPON_SWORD,
	WEAPON_ARROW,

	WEAPON_END,
};

enum SKILLKEYS
{
	KEY_Q,
	KEY_E,
	KEY_R,

	KEY_END
};



class UNREALPROJ_API DEFINE
{
public:
	DEFINE();
	~DEFINE();
};
