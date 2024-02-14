// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../../Interface/Interactable.h"
#include "InteractObject.generated.h"

UCLASS()
class UNREALPROJ_API AInteractObject : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	AInteractObject();
protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void Interact(class AMyPlayer* Player) override;

protected:
	UPROPERTY(EditAnywhere)
		class USkeletalMeshComponent* Mesh;

	UPROPERTY()
		class UCapsuleComponent* CapsuleComponent;

	UPROPERTY()
		class UBoxComponent* InteractBox;
};
