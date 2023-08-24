// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Monster.h"
#include "SpawnMonster.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJ_API ASpawnMonster : public AMonster
{
	GENERATED_BODY()
public:
	ASpawnMonster();

protected:
	virtual void PostInitializeComponents() override;

public:
	TWeakObjectPtr<class AMonsterSpawner> GetSpawner() { return Spawner; }
	void SetSpawner(TWeakObjectPtr<class AMonsterSpawner> Value) { Spawner = Value; }

	virtual void AttackTarget() override;
	virtual void AttackCheck() override;
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser);
	virtual void Die(class AMyPlayer* Player) override;
	virtual void DestroyObject() override;

private:
	void SetHpBar();
private:
	UPROPERTY()
	TWeakObjectPtr<class AMonsterSpawner> Spawner;

	UPROPERTY()
	class UMonsterAnimInstance* AnimInst;

	UPROPERTY()
	class UWidgetComponent* HpBar;
};
