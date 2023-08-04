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
	Skill,
	Information,

	End,
};

UENUM(BlueprintType)
enum class STATE : uint8
{
	IDLE,
	MOVE,
	JUMP,
	ATTACK,
	DAMAGED,
	SKILL,
	SKILLCAST,
	PULLED,
	HITANDFALL,
	KNOCKED,
	REVIVE,
};

UENUM(BlueprintType)
enum class WEAPONTYPE : uint8
{
	WEAPON_SWORD,
	WEAPON_ARROW,

	WEAPON_END,
}; //���⵵ �� ����ϰ� ������ �ʿ䰡..

UENUM(BlueprintType)
enum class AttackType : uint8
{
	NONE,
	NORMAL, // �⺻ �����
	STRONG, // ������ - ����
	THRUST, // ��ġ�� ���� - ���� + �з���
	DOWN,
	HITANDFALL, // ���󰡼� �Ѿ���
};

enum ItemType
{
	ITEM_SWORD,
	ITEM_BOW,
	ITEM_USE
};



enum UseItemType
{
	ITEM_HP,
	ITEM_MP,
	ITEM_HPMP,
};

enum InformationType
{
	INFO_WEAPON,
	INFO_USEITEM,
	INFO_SWORDSKILL,
	INFO_BOWSKILL,
};
enum InventoryType
{
	Equip,
	Use,
	Etc,
};

enum class DragType
{
	Skill,
	Item,
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
