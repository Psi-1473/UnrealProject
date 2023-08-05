// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../../Interface/Interactable.h"
#include "LootObject.generated.h"

UCLASS()
class UNREALPROJ_API ALootObject : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	ALootObject();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void Interact() override;
private:
	UPROPERTY(EditAnywhere)
		class USkeletalMeshComponent* Mesh;

	UPROPERTY()
		class UCapsuleComponent* CapsuleComponent;

	UPROPERTY()
		class UBoxComponent* InteractBox;
};
