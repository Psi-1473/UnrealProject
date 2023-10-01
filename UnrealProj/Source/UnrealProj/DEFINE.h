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
	Looting,
	BossHpBar,
	NpcQuest,
	NpcQuestSlot,
	NpcQuestInfo,
	NpcQuestClear,
	Quest,
	QuestSlot,
	QuestInfo,
	QuestQuickInfo,
	LineScript,
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
	PULLED, // �������� ����
	HITANDFALL, // ���ݸ°� ���ư��� ��
	KNOCKED, // ���ݸ°� �ٿ�
	REVIVE,
	LOOT,
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
	PULLED, // ��� ���鼭 ���������� Damaged �� -> Montage�� ����
	HITANDFALL, // ���󰡼� �Ѿ���
	// STRONG�� PULLED�� �ִϸ��̼��� ������
	// STRONG�� STATE ����
	// PULLED�� Montage ����
};



UENUM(BlueprintType)
enum class QuestLevel : uint8
{
	NONE,
	MAIN,
	SUB,
};

enum QuestType
{
	QUEST_EMPTY,
	QUEST_NORMAL,
	QUEST_HUNT,
	QUEST_ITEM,
	QUEST_ETC,
	QUEST_INVESTIGATE,
};

enum EctQuestType
{
	ETC_EMPTY,
	ETC_QUICKSLOT,

};
enum QuestItemType
{
	QITEM_NONE,
	QITEM_EQUIP,
	QITEM_USE,
	QITEM_ETC,
};
enum ItemType
{
	ITEM_SWORD,
	ITEM_BOW,
	ITEM_USE
};

enum CameraShakeType
{
	SHAKE_BASIC,
	SHAKE_SKILL,
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
