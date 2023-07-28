// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../../DEFINE.h"
#include "../../MyGameInstance.h"
#include "MyPlayer.generated.h"

UCLASS()
class UNREALPROJ_API AMyPlayer : public ACharacter
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

public:
	class UPlayerAnim* GetAnimInst() { return AnimInst; }
	class UCharacterState* GetState();
	class UCharacterState* GetSpecificState(STATE Value);
	class AWeapon* GetWeapon() { return EquipedWeapon; }
	class UCameraComponent* GetCamera() { return Camera; }
	class UPlayerStatComponent* GetStatComponent() { return StatComponent; }
	class UPlayerSkillComponent* GetSkillComponent() { return SkillComponent; }
	class UInventory* GetInventory() { return Inventory; }
	class ASkillRangeActor* GetSpawnedRangeActor() { return SpawnedRangeActor; }
	class UMyGameInstance* GetInstance() { return GInstance; }
	FVector GetArrowMuzzle() { return MuzzleOffset; }
	FVector GetPullPos() { return PullPos; }
	class UPlayerSkill* GetSkill() { return ExecuteSkill; }
	bool GetDash() { return bDash; }


	void SetInteractingNpc(class ANpc* Npc) { InteractingNpc = Npc; }
	void SetRangeActor(class ASkillRangeActor* Value) { SpawnedRangeActor = Value; }
	void SetState(STATE Value);
	void SetSkill(class UPlayerSkill* Value) { ExecuteSkill = Value; }
	void SetDash(bool Value) { bDash = Value; }
	void SetPullPos(FVector Value) { PullPos = Value; }

public:
	void EquipWeapon(AWeapon* _Weapon); // ���� ���� �Լ�
	void AttackCheck(float UpRange, float FrontRange, float SideRange);
	void Interact();

public:
	void SetFlyMode(float Speed);
	void SetWalkMode(float Speed = 600.f);
private:
	void SetDefaultCamera(); // �����ڿ��� ī�޶� ����
	void SetWeaponSocket();
	void SetAnimByWeapon(WEAPONTYPE Type); // ���⿡ ���� �ִϸ��̼� ����
	

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
	// ������ �ִϸ��̼ǵ��� TArray�� ������ ������ ���߿�
	// ����ó�� ��Ȳ�� �´� ABP �����ͼ� �����ϱ�

	UPROPERTY(EditAnywhere)
	class UPlayerAnim* AnimInst;

	UPROPERTY()
	class UPlayerStatComponent* StatComponent;

	UPROPERTY()
	class UPlayerSkillComponent* SkillComponent;

	UPROPERTY()
	class ASkillRangeActor* SpawnedRangeActor;

	UPROPERTY()
	class UInventory* Inventory;

private:
	UPROPERTY()
	FVector PullPos;

	UPROPERTY()
	class UMyGameInstance* GInstance;

	UPROPERTY()
	class ANpc* InteractingNpc;
};
