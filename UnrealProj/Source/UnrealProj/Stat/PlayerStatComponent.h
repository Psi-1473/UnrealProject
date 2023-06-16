// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerStatComponent.generated.h"


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

	void SetLevel(int32 NewLevel);
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
};
