// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "MyPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJ_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AMyPlayerController();

	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	float GetHorizontal() { return Horizontal; }
	float GetVertical() { return Vertical; }
	bool GetIsZoom() { return bZoom; }
public:
	void Fire();
	void FireArrow(FVector DestPos);

private:
	void IA_Move(const FInputActionValue& Value);
	void IA_Look(const FInputActionValue& Value);
	void IA_Jump(const FInputActionValue& Value);
	void IA_Zoom(const FInputActionValue& Value);
	void IA_Push_Q(const FInputActionValue& Value);
	void IA_Push_E(const FInputActionValue& Value);
	void IA_Push_R(const FInputActionValue& Value);
	void IA_Inventory(const FInputActionValue& Value);
	void IA_Interact(const FInputActionValue& Value);
	void IA_Skill(const FInputActionValue& Value);
	void IA_Quick1(const FInputActionValue& Value);
	void IA_Quick2(const FInputActionValue& Value);
	void IA_Quick3(const FInputActionValue& Value);
	

	void IA_Sword_Attack(const FInputActionValue& Value);

	FVector GetViewportToWorld();
	FVector GetArrowDir(FVector Start, FVector Dir);
private:
	void ZoomIn();
	void ZoomOut();

private:
	bool CameraMoved = false;

	UPROPERTY()
	float MouseSpeed = 2.f;

	UPROPERTY()
	float Horizontal;

	UPROPERTY()
	float Vertical;

	UPROPERTY(VisibleAnywhere)
	int bCombo = 1;

	UPROPERTY(VisibleAnywhere)
	bool bZoom = false;

private:
	UPROPERTY(VisibleAnywhere, Category = Input)
	class UInputMappingContext* DefaultContext;

	UPROPERTY(VisibleAnywhere, Category = Input)
	class UInputAction* MoveAction;

	UPROPERTY(VisibleAnywhere, Category = Input)
	class UInputAction* LookAction;

	UPROPERTY(VisibleAnywhere, Category = Input)
	class UInputAction* JumpAction;

	UPROPERTY(VisibleAnywhere, Category = Input)
	class UInputAction* Action_AttackSword;

	UPROPERTY(VisibleAnywhere, Category = Input)
	class UInputAction* ZoomAction;

	UPROPERTY(VisibleAnywhere, Category = Input)
	class UInputAction* Push_Q;

	UPROPERTY(VisibleAnywhere, Category = Input)
	class UInputAction* Push_E;

	UPROPERTY(VisibleAnywhere, Category = Input)
	class UInputAction* Push_R;

	UPROPERTY(VisibleAnywhere, Category = Input)
	class UInputAction* InvenAction;

	UPROPERTY(VisibleAnywhere, Category = Input)
	class UInputAction* InteractAction;

	UPROPERTY(VisibleAnywhere, Category = Input)
	class UInputAction* SkillUIAction;

	UPROPERTY(VisibleAnywhere, Category = Input)
	class UInputAction* Quick1;

	UPROPERTY(VisibleAnywhere, Category = Input)
	class UInputAction* Quick2;

	UPROPERTY(VisibleAnywhere, Category = Input)
	class UInputAction* Quick3;
	UPROPERTY(VisibleAnywhere)
	class AMyPlayer* MyPlayer;
};
