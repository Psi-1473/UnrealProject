// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../../Interface/SoundActor.h"
#include "Monster.generated.h"


UCLASS()
class UNREALPROJ_API AMonster : public ACharacter, public ISoundActor
{
	GENERATED_BODY()

public:
	AMonster();

protected:
	virtual void BeginPlay();
	virtual void PostInitializeComponents();

public:	
	virtual void Tick(float DeltaTime);


	FString GetObjectName();

public:
	virtual void AttackTarget() {};
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser);
	//virtual void OnDamaged(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser, AttackType Type = AttackType::NORMAL);
	virtual void Die(class AMyPlayer* Player) {};
	virtual void DestroyObject();

	virtual void AttackCheck() {};
protected:
	void PopupDamageText(float Damage);

public:
	bool bDeath = false;
protected:


	UPROPERTY()
	class UMonsterStatComponent* StatComponent;

	UPROPERTY(EditAnywhere)
	class USceneComponent* DamageTextComp;

	UPROPERTY()
	FTimerHandle DestroyTimerHandle;

	UPROPERTY(EditAnywhere)
	class UAudioComponent* AudioComponent;


};
