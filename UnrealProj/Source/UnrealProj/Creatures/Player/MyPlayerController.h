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

private:
	void IA_Move(const FInputActionValue& Value);
	void IA_Look(const FInputActionValue& Value);
	void IA_Jump(const FInputActionValue& Value);

private:
	UPROPERTY()
	float MouseSpeed = 2.f;

private:
	UPROPERTY(VisibleAnywhere, Category = Input)
	class UInputMappingContext* DefaultContext;

	UPROPERTY(VisibleAnywhere, Category = Input)
	class UInputAction* MoveAction;

	UPROPERTY(VisibleAnywhere, Category = Input)
	class UInputAction* LookAction;

	UPROPERTY(VisibleAnywhere)
	class AMyPlayer* MyPlayer;
};
