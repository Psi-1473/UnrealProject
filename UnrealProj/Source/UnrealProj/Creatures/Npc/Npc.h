// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../../DEFINE.h"
#include "Npc.generated.h"

UCLASS()
class UNREALPROJ_API ANpc : public AActor
{
	GENERATED_BODY()
	
public:	
	ANpc();

protected:
	virtual void BeginPlay() override;

public:
	int16 GetId() { return Id; }
	FString GetName() { return Name; }
	FString GetDefaultLine() { return DefaultLine; }
protected:
	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:
	void Interact();
private:
	void GetIdFromActor();
	void SetNpcInfo();

protected:
	NpcType Type;

	UPROPERTY()
	int16 Id;

	UPROPERTY()
	FString Name;

	UPROPERTY()
	FString DefaultLine;

	UPROPERTY(EditAnywhere)
	class USkeletalMeshComponent* Mesh;

	UPROPERTY()
	class UCapsuleComponent* CapsuleComponent;

	UPROPERTY()
	class UBoxComponent* InteractBox;
};
