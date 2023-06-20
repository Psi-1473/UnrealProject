// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class STATE : uint8
{
	IDLE,
	MOVE,
	JUMP,
	ATTACK,
	SKILL,
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
