// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../../DEFINE.h"
#include "../../Interface/SoundActor.h"
#include "../../MyGameInstance.h"
#include "MyPlayer.generated.h"

UCLASS()
class UNREALPROJ_API AMyPlayer : public ACharacter, public ISoundActor
{
	GENERATED_BODY()

public:
	AMyPlayer();

protected:
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void OnDamaged(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser, AttackType Type = AttackType::NORMAL);
	void Die();
	void Revive();

	void EquipWeapon(class AWeapon* _Weapon); // 무기 장착 함수
	void AttackCheck(float UpRange, float FrontRange, float SideRange);
	void Interact();
	void ShakeCamera(CameraShakeType Type); //class ULegacyCameraShake CameraShake 매개변수 추가해서 변경하기
	void ShakeCamera(TSubclassOf<class ULegacyCameraShake> Type);

public:
	class UCharacterState* GetState();
	class UWeaponState* GetWeaponState();
	class UCharacterState* GetSpecificState(STATE Value);


	class UPlayerAnim* GetAnimInst() { return AnimInst; }
	class AWeapon* GetWeapon() { return EquipedWeapon; }
	class UCameraComponent* GetCamera() { return Camera; }
	class UPlayerSkill* GetSkill() { return ExecuteSkill; }
	
	/*
		Get Components
	*/
	class UPlayerStatComponent* GetStatComponent() { return StatComponent; }
	class UPlayerSkillComponent* GetSkillComponent() { return SkillComponent; }
	class UPlayerQuestComponent* GetQuestComponent() { return QuestComponent; }
	class UBuffComponent* GetBuffComponent() { return BuffComponent; }
	class UInventory* GetInventory() { return Inventory; }


	/*
		Get Misc.
	*/
	class ASkillRangeActor* GetSpawnedRangeActor() { return SpawnedRangeActor; }
	class UMyGameInstance* GetInstance() { return GInstance; }
	FVector GetArrowMuzzle() { return MuzzleOffset; }
	bool GetDash() { return bDash; }


	void SetInteractObj(TScriptInterface<class IInteractable> Obj) { InteractObj = Obj; }
	void SetRangeActor(class ASkillRangeActor* Value) { SpawnedRangeActor = Value; }
	void SetState(STATE Value);
	void SetSkill(class UPlayerSkill* Value) { ExecuteSkill = Value; }
	void SetDash(bool Value) { bDash = Value; }

public:


private:
	/*
	Initialize or Setting Functions
	*/
	void InitDefaultCamera();
	void InitWeaponSocket();
	void InitAssets();
	void CreateComponents();
	void InitializeComponents();
	void SetEngineVariables();

	void SetAnimByWeapon(WEAPONTYPE Type); // 무기에 따라 애니메이션 변경
	

	// Common variables
private:
	UPROPERTY(EditAnywhere)
	class AWeapon* EquipedWeapon;

	UPROPERTY()
	class UPlayerSkill* ExecuteSkill;

	UPROPERTY()
	bool bDash = false;

	// Components
private:
	UPROPERTY(EditAnywhere)
	FVector MuzzleOffset;
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* LWeapon;

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* RWeapon;

	UPROPERTY(EditAnywhere)
	class UStateMachine* StateMachine;

	UPROPERTY(EditAnywhere)
	class UCameraComponent* Camera;

	UPROPERTY(EditAnywhere)
	class USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<class UAnimInstance>> AnimClasses;

	UPROPERTY(EditAnywhere)
	class UPlayerAnim* AnimInst;

	UPROPERTY()
	class UPlayerStatComponent* StatComponent;

	UPROPERTY()
	class UPlayerQuestComponent* QuestComponent;

	UPROPERTY()
	class UPlayerSkillComponent* SkillComponent;

	UPROPERTY()
	class UBuffComponent* BuffComponent;

	UPROPERTY()
	class UInventory* Inventory;

	UPROPERTY()
	class ASkillRangeActor* SpawnedRangeActor;


private:
	UPROPERTY()
	class UMyGameInstance* GInstance;

	UPROPERTY()
	TScriptInterface<class IInteractable> InteractObj;

	UPROPERTY(EditAnywhere)
	class UAudioComponent* AudioComponent;

};
