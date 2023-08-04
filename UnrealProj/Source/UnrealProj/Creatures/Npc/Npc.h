// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../../DEFINE.h"
#include "../../Interface/Interactable.h"
#include "Npc.generated.h"

UCLASS()
class UNREALPROJ_API ANpc : public AActor, public IInteractable
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
	NpcType GetNpcType() { return Type; }
	TArray<int16> GetSwordIds() { return SwordIds; }
	TArray<int16> GetBowIds() { return BowIds; }
	TArray<int16> GetUseItemIds() { return UseItemIds; }
	int16 GetItemSize() { return BowIds.Num() + SwordIds.Num() + UseItemIds.Num(); }
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

protected:
	UPROPERTY(EditAnywhere)
	TArray<int16> SwordIds;

	UPROPERTY(EditAnywhere)
	TArray<int16> BowIds;

	UPROPERTY(EditAnywhere)
	TArray<int16> UseItemIds;

	// �� �߰��ϸ� ����Ʈ�� �߰�
	// + �������Ʈ���� ���� C++ ��ũ��Ʈ���� �� �� �ִ� ������� Ȯ��
};
