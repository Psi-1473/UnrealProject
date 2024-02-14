// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#define SLOTINDEX_NOT_SPECIFIED -1
#define FIND_FAILED -1
const int8 MAX_Inventory = 18;
const FString DROPITEMTEXT = TEXT("/Script/Engine.Blueprint'/Game/02_Blueprints/InteractObj/DropItemPocket.DropItemPocket_C'");

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
	AreaTitle,
	Revive,
	ItemDrop,
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
	DEAD,
	SKILL,
	SKILLCAST,
	PULLED,
	HITANDFALL,
	KNOCKED,
	REVIVE,
	RESPAWN,
	LOOT,
	INTERACT,
};



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
enum class SkillEnum : uint8
{
	SKILL_SWORD_1,
	SKILL_SWORD_2,
	SKILL_SWORD_3,
	SKILL_BOW_1,
	SKILL_BOW_2,
	SKILL_BOW_3,
};

UENUM(BlueprintType)
enum class QuestLevel : uint8
{
	NONE,
	MAIN,
	SUB,
};

UENUM(BlueprintType, meta = (Bitflags, UseEnumValuesAsMaskValuesInEditor = "true"))
enum class EDebuff : uint8
{
	None = 0 UMETA(Hidden),
	Burning = 1 << 0,
	Poison = 1 << 1,
	Freeze = 1 << 2,
	NoHeal = 1 << 3,
	Silence = 1 << 4,
	NoJump = 1 << 5,
	DecreaseAttack = 1 << 6,
	DecreaseDefense = 1 << 7,
};

UENUM(BlueprintType)
enum class ENEMY_ATTACKT_TYPE : uint8
{
	MELEE,
	BOW,
	MAGIC,
};

UENUM(BlueprintType)
enum class WEAPONTYPE : uint8
{
	/*
		스킬, 공격 등에서 무기에 따라 뭔갈 나눌 때 사용
	*/
	WEAPON_SWORD,
	WEAPON_BOW,

	WEAPON_NONE,
	WEAPON_END,
};

enum ItemType
{
	/*
		Item Data를 불러올 때, 어떤 데이터에 접근할 지를 결정할 때 사용
	*/
	ITEM_SWORD,
	ITEM_BOW,
	ITEM_USE,
	ITEM_MISC,
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

