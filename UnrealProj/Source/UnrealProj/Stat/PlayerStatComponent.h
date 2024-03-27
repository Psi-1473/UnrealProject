// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerStatComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnHpChanged);
DECLARE_MULTICAST_DELEGATE(FOnMpChanged);
DECLARE_MULTICAST_DELEGATE(FOnExpChanged);
DECLARE_MULTICAST_DELEGATE(FOnLevelChanged);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREALPROJ_API UPlayerStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UPlayerStatComponent();

protected:
	virtual void BeginPlay() override;
	virtual void InitializeComponent() override;
	


public:	
	int32 GetLevel() { return Level; }
	int32 GetAttack() { return Attack; }
	int32 GetMaxHp() { return MaxHp; }
	int32 GetMaxMp() { return MaxMp; }
	int32 GetMaxExp() { return MaxExp; }
	int32 GetExp() { return Exp; }

	float GetHpRatio() { return Hp / (float)MaxHp; }
	float GetMpRatio() { return Mp / (float)MaxMp; }
	float GetExpRatio() { return Exp / (float)MaxExp; }
	int32 GetHp() { return Hp; }
	int32 GetMp() { return Mp; }

	void SetLevel(int32 NewLevel);
	void AddExp(int32 Value);
	void SetHp(int32 Value);
	void SetExp(int32 Value);
	void SetMp(int32 Value);
	void AddHp(int Value);
	void AddMp(int Value);
public:
	void OnAttacked(float DamageAmount);

private:
	UPROPERTY()
	int32 Level;
	
	UPROPERTY()
	int32 Attack;

	UPROPERTY()
	int32 MaxHp;

	UPROPERTY()
	int32 Hp;

	UPROPERTY()
	int32 MaxExp;

	UPROPERTY()
	int32 Exp;

	UPROPERTY()
	int32 MaxMp;

	UPROPERTY()
	int32 Mp;

public:
	FOnHpChanged OnHpChanged;
	FOnMpChanged OnMpChanged;
	FOnExpChanged OnExpChanged;
	FOnLevelChanged OnLevelChanged;

private:
	UPROPERTY()
	UParticleSystem* LevelUpEffect;
};
