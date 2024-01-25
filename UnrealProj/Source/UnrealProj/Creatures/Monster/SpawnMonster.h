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

	bool GetChase() { return bChase; }
public:
	TWeakObjectPtr<class AMonsterSpawner> GetSpawner() { return Spawner; }
	void SetSpawner(TWeakObjectPtr<class AMonsterSpawner> Value) { Spawner = Value; }

public:
	void SucceedFindingTarget();
	void TargetOutOfRange();

	virtual void OnDamaged(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser, class UParticleSystem* Particle, AttackType Type = AttackType::NORMAL) override;
	virtual void Die(class AMyPlayer* Player) override;
	virtual void DestroyObject() override;
	virtual void AttackCheck() override;

private:
	void SetHpBar();
	void SetMarkUI();
	void RevealHpBar();
	void HideHpBar();
	void CheckDistance();

	
private:
	UPROPERTY()
	bool bChase = false;

	UPROPERTY()
	TWeakObjectPtr<class AMonsterSpawner> Spawner;

	UPROPERTY()
	TWeakObjectPtr<class AMyPlayer> Attacker;

	UPROPERTY(EditAnywhere)
	class UWidgetComponent* HpBar;

	UPROPERTY(EditAnywhere)
	class UWidgetComponent* MarkUI;

	UPROPERTY()
	struct FTimerHandle HideHpBarTimer;
};
