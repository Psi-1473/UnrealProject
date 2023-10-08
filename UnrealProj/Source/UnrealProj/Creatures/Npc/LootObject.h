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

	virtual void Interact(class AMyPlayer* Player) override;
	void LootEnd();
	void LootCancle();

public:
	int32 GetId() {return Id;}

private:
	void RegisterToManager();

private:
	UPROPERTY(EditAnywhere)
	int32 Id;

	UPROPERTY(EditAnywhere)
	float Time = 7.f;

	UPROPERTY()
	TWeakObjectPtr<class AMyPlayer> InteractingPlayer;
private:
	UPROPERTY(EditAnywhere)
		class USkeletalMeshComponent* Mesh;

	UPROPERTY()
		class UCapsuleComponent* CapsuleComponent;

	UPROPERTY()
		class UBoxComponent* InteractBox;
};
