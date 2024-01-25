// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../../Interface/SoundActor.h"
#include "../../DEFINE.h"
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


	/*
		Get / Set
	*/ 
	int GetObjectId();
	bool GetDeath() { return bDeath; }


	class UAudioComponent* GetAudioComponent() { return AudioComponent; }
	class UMonsterStatComponent* GetStatComponent() { return StatComponent; }


	void SetTargetUI(bool Value);
public:
	virtual void AttackTarget(class AMyPlayer* Target);
	virtual void OnDamaged(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, 
		AActor* DamageCauser, class UParticleSystem* Particle = nullptr, AttackType Type = AttackType::NORMAL) {};
	virtual void Die(class AMyPlayer* Player) {};
	virtual void DestroyObject() {};
	virtual void AttackCheck() {};
	

protected:
	void PopupDamageText(float Damage);

	/*
		Attack Check
	*/
	void AttackMelee();
	void AttackBow();
	void AttackMagic();
	/*
		Init Func
	*/
	void InitTargetUI();
	void InitWeaponSocket();

protected:
	UPROPERTY()
	class UEnemyAnimInstance* AnimInst;
	UPROPERTY()
	bool bDeath = false;

	UPROPERTY()
	class UMonsterStatComponent* StatComponent;

	UPROPERTY(EditAnywhere)
	class USceneComponent* DamageTextComp;

	UPROPERTY()
	FTimerHandle DestroyTimerHandle;

	UPROPERTY(EditAnywhere)
	class UAudioComponent* AudioComponent;

	UPROPERTY(EditAnywhere)
	class UWidgetComponent* TargetUI;

	UPROPERTY(EditAnywhere)
		class UStaticMeshComponent* LWeapon;

	UPROPERTY(EditAnywhere)
		class UStaticMeshComponent* RWeapon;
};
