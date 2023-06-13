// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../../DEFINE.h"
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
	FVector GetArrowMuzzle() { return MuzzleOffset; }

	void SetState(STATE Value);

public:
	void EquipWeapon(AWeapon* _Weapon); // ���� ���� �Լ�

private:
	void SetDefaultCamera(); // �����ڿ��� ī�޶� ����
	void SetWeaponSocket();
	void SetAnimByWeapon(WEAPONTYPE Type); // ���⿡ ���� �ִϸ��̼� ����

	// Common variables
private:
	class AWeapon* EquipedWeapon;


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
};
