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
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser);

	virtual void OnDamaged(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser, AttackType Type = AttackType::NORMAL);
	void Die();
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
	class UPlayerSkill* GetSkill() { return ExecuteSkill; }
	bool GetDash() { return bDash; }


	void SetInteractingNpc(class ANpc* Npc) { InteractingNpc = Npc; }
	void SetRangeActor(class ASkillRangeActor* Value) { SpawnedRangeActor = Value; }
	void SetState(STATE Value);
	void SetSkill(class UPlayerSkill* Value) { ExecuteSkill = Value; }
	void SetDash(bool Value) { bDash = Value; }

public:
	void EquipWeapon(AWeapon* _Weapon); // 무기 장착 함수
	void AttackCheck(float UpRange, float FrontRange, float SideRange);
	void Interact();

private:
	void SetDefaultCamera(); // 생성자에서 카메라 생성
	void SetWeaponSocket();
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
	// 지금은 애니메이션들을 TArray로 가지고 있지만 나중에
	// 무기처럼 상황에 맞는 ABP 가져와서 실행하기

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
	class UMyGameInstance* GInstance;

	UPROPERTY()
	class ANpc* InteractingNpc;
};
