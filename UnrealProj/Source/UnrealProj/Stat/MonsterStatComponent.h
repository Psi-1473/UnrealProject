// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "../DEFINE.h"
#include "MonsterStatComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnHpChanged);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREALPROJ_API UMonsterStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UMonsterStatComponent();

protected:
	virtual void BeginPlay() override;
	virtual void InitializeComponent() override;

public:	
	FString GetMonsterName() { return Name; }
	int32 GetId() { return Id; }
	int32 GetLevel() { return Level; }
	int32 GetAttack() { return Attack; }
	int32 GetMaxHp() { return MaxHp; }
	int32 GetHp() { return Hp; }
	int32 GetExp() { return Exp; }
	int32 GetGold() { return FMath::RandRange(MinGold, MaxGold);}
	ENEMY_ATTACKT_TYPE GetAttackType() { return AttackType; }

	float GetHpRatio() { return Hp / (float)MaxHp; }
public:
	void SetInfo(int MonsterId);
	void SetHp(int32 NewHp);
	void OnAttacked(float Damage);
private:
	UPROPERTY()
	FString Name;

	UPROPERTY()
	int32 Id;

	UPROPERTY()
	int32 Level;

	UPROPERTY()
	int32 Attack;

	UPROPERTY()
	int32 MaxHp;

	UPROPERTY()
	int32 Hp;

	UPROPERTY()
	int32 Exp;

	UPROPERTY()
	int32 MaxGold;

	UPROPERTY()
	int32 MinGold;

	UPROPERTY()
	ENEMY_ATTACKT_TYPE AttackType;

public:
	FOnHpChanged OnHpChanged;
};
