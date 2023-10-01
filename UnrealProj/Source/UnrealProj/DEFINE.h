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
	PULLED, // 끌려가는 상태
	HITANDFALL, // 공격맞고 날아가는 중
	KNOCKED, // 공격맞고 다운
	REVIVE,
	LOOT,
};

UENUM(BlueprintType)
enum class WEAPONTYPE : uint8
{
	WEAPON_SWORD,
	WEAPON_ARROW,

	WEAPON_END,
}; //여기도 좀 깔끔하게 정리할 필요가..

UENUM(BlueprintType)
enum class AttackType : uint8
{
	NONE,
	NORMAL, // 기본 약공격
	STRONG, // 강공격 - 경직
	THRUST, // 밀치기 공격 - 경직 + 밀려남
	DOWN,
	PULLED, // 잡아 당기면서 지속적으로 Damaged 줌 -> Montage로 구현
	HITANDFALL, // 날라가서 넘어짐
	// STRONG과 PULLED의 애니메이션은 같지만
	// STRONG은 STATE 구현
	// PULLED는 Montage 구현
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
