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
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;

public:
	virtual void Tick(float DeltaTime) override;
public:
	TWeakObjectPtr<class AMonsterSpawner> GetSpawner() { return Spawner; }
	void SetSpawner(TWeakObjectPtr<class AMonsterSpawner> Value) { Spawner = Value; }

public:
	virtual void AttackTarget(class AMyPlayer* Target) override;
	virtual void OnDamaged(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser, class UParticleSystem* Particle, AttackType Type = AttackType::NORMAL) override;
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	virtual void Die(class AMyPlayer* Player) override;
	virtual void DestroyObject() override;
	virtual void AttackCheck() override;

private:
	void SetHpBar();
	void RevealHpBar();
	void HideHpBar();
	void CheckDistance();

private:
	UPROPERTY()
	TWeakObjectPtr<class AMonsterSpawner> Spawner;

	UPROPERTY()
	TWeakObjectPtr<class AMyPlayer> Attacker;

	UPROPERTY()
	class UMonsterAnimInstance* AnimInst;

	UPROPERTY()
	class UWidgetComponent* HpBar;

	UPROPERTY()
	struct FTimerHandle AttackerTimer;
};
