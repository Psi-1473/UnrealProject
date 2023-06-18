// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Monster.generated.h"


UCLASS()
class UNREALPROJ_API AMonster : public ACharacter
{
	GENERATED_BODY()

public:
	AMonster();

protected:
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;

public:	
	virtual void Tick(float DeltaTime) override;


	FString GetObjectName();

public:
	void AttackTarget(class AMyPlayer* Target);
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	void Die();
	void DestroyObject();
private:
	void SetHpBar();
	void PopupDamageText(float Damage);

public:
	//temp
	bool bDeath = false;
private:
	UPROPERTY()
	class UMonsterAnimInstance* AnimInst;

	UPROPERTY()
	class UMonsterStatComponent* StatComponent;

	UPROPERTY(EditAnywhere)
	class USceneComponent* DamageTextComp;

	UPROPERTY()
	class UWidgetComponent* HpBar;

	UPROPERTY()
	FTimerHandle DestroyTimerHandle;


};
