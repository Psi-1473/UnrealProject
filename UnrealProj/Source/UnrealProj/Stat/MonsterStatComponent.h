// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
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
	FString GetName() { return Name; }
	int32 GetId() { return Id; }
	int32 GetLevel() { return Level; }
	int32 GetAttack() { return Attack; }
	int32 GetMaxHp() { return MaxHp; }
	int32 GetHp() { return Hp; }

	float GetHpRatio() { return Hp / (float)MaxHp; }
public:
	void SetInfo(FString NameInfo);
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

public:
	FOnHpChanged OnHpChanged;
};
