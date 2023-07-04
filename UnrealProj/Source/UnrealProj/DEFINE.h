// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


const int8 MAX_Inventory = 18;


UENUM(BlueprintType)
enum class UIType : uint8
{
	Inventory,
	Script,
	Shop,

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

enum ItemType
{
	ITEM_SWORD,
	ITEM_BOW,
	ITEM_USE
};
enum WEAPONTYPE
{
	WEAPON_SWORD,
	WEAPON_ARROW,

	WEAPON_END,
}; //여기도 좀 깔끔하게 정리할 필요가..


enum UseItemType
{
	ITEM_HP,
	ITEM_MP,
	ITEM_HPMP,
};

enum InventoryType
{
	Equip,
	Use,
	Etc,
};



enum SKILLKEYS
{
	KEY_Q,
	KEY_E,
	KEY_R,

	KEY_END
};

enum NpcType
{
	NONE_SHOP,
	EQUIP_SHOP,
	USE_SHOP,
};

class UNREALPROJ_API DEFINE
{
public:
	DEFINE();
	~DEFINE();
};
