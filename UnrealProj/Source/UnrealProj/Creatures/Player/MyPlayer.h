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

	void Interact();

	void SetAnimByWeapon(WEAPONTYPE Type); // 무기에 따라 애니메이션 변경
public:
	class UStateMachine* GetStateMachine() { return StateMachine; }

	class UPlayerAnim* GetAnimInst() { return AnimInst; }
	class UCameraComponent* GetCamera() { return Camera; }
	class UPlayerSkill* GetSkill() { return ExecuteSkill; }
	
	/*
		Get Components Func.
	*/
	class UPlayerStatComponent* GetStatComponent() { return StatComponent; }
	class UEquipItemComponent* GetEquipComponent() { return EquipComponent; }
	class UPlayerSkillComponent* GetSkillComponent() { return SkillComponent; }
	class UPlayerQuestComponent* GetQuestComponent() { return QuestComponent; }
	class UBuffComponent* GetBuffComponent() { return BuffComponent; }
	class UInventory* GetInventory() { return Inventory; }
	class UVehicleComponent* GetVehicleComponent() { return VehicleComponent; }
	class UCameraEffectComponent* GetCameraEffectComponent() { return CameraEffectComponent; }


	/*
		Get Misc.
	*/
	class UStaticMeshComponent* GetLeftWeaponMesh() { return LWeapon; }
	class UStaticMeshComponent* GetRightWeaponMesh() { return RWeapon; }
	class ASkillRangeActor* GetSpawnedRangeActor() { return SpawnedRangeActor; }
	class UMyGameInstance* GetInstance() { return GInstance; }
	FVector GetArrowMuzzle() { return MuzzleOffset; }
	bool GetDash() { return bDash; }


	void SetInteractObj(TScriptInterface<class IInteractable> Obj) { InteractObj = Obj; }
	void SetRangeActor(class ASkillRangeActor* Value) { SpawnedRangeActor = Value; }
	void SetSkill(class UPlayerSkill* Value) { ExecuteSkill = Value; }
	void SetDash(bool Value) { bDash = Value; }
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

	
	

	// Common variables
private:
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

	/*
	 Components
	*/
	UPROPERTY()
	class UPlayerStatComponent* StatComponent;
	UPROPERTY()
	class UPlayerQuestComponent* QuestComponent;
	UPROPERTY()
	class UPlayerSkillComponent* SkillComponent;
	UPROPERTY()
	class UEquipItemComponent* EquipComponent;
	UPROPERTY()
	class UBuffComponent* BuffComponent;
	UPROPERTY()
	class UInventory* Inventory;
	UPROPERTY()
	class UVehicleComponent* VehicleComponent;
	UPROPERTY()
	class UCameraEffectComponent* CameraEffectComponent;

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
