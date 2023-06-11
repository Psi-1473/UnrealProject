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

private:
	void IA_Move(const FInputActionValue& Value);
	void IA_Look(const FInputActionValue& Value);
	void IA_Jump(const FInputActionValue& Value);
	void IA_Zoom(const FInputActionValue& Value);

	void IA_Sword_Attack(const FInputActionValue& Value);

private:
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

	UPROPERTY(VisibleAnywhere)
	class AMyPlayer* MyPlayer;
};
