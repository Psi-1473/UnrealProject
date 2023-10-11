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
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

public:
	int16 GetId() { return Id; }
	FString GetNpcName() { return Name; }
	FString GetNpcJob() { return Job; }
	FString GetDefaultLine() { return DefaultLine; }
	NpcType GetNpcType() { return Type; }
	TArray<int16> GetSwordIds() { return SwordIds; }
	TArray<int16> GetBowIds() { return BowIds; }
	TArray<int16> GetUseItemIds() { return UseItemIds; }
	int16 GetItemSize() { return BowIds.Num() + SwordIds.Num() + UseItemIds.Num(); }
	class UQuestComponent* GetQuestComponent() { return QuestComponent; }
	class UPaperSprite* GetSprite(FString SpriteName);
public:
	virtual void Interact(class AMyPlayer* Player) override;
	void LoadPossibleQuestData(class AMyPlayer* Player);
	void UpdateQuestMark();
private:
	void GetIdFromActor();
	void SetNpcInfo();
	void SetMinimapIcon();
	void SetPlayer();
	void SetVisiblityInfoWidget();

protected:
	NpcType Type;

	UPROPERTY()
	int16 Id;

	UPROPERTY()
	FString Job;

	UPROPERTY()
	FString Name;

	UPROPERTY()
	FString DefaultLine;

	UPROPERTY(EditAnywhere)
	class USkeletalMeshComponent* Mesh;

	UPROPERTY(EditAnywhere)
	class UPaperSpriteComponent* MinimapIcon;


	UPROPERTY()
	class UCapsuleComponent* CapsuleComponent;

	UPROPERTY()
	class UQuestComponent* QuestComponent;

	UPROPERTY()
	class UBoxComponent* InteractBox;

	UPROPERTY(EditAnywhere)
	class UWidgetComponent* NpcInfo;
	
	UPROPERTY()
	TWeakObjectPtr<class AMyPlayer> MainPlayer;

protected:
	UPROPERTY(EditAnywhere)
	TArray<int16> SwordIds;

	UPROPERTY(EditAnywhere)
	TArray<int16> BowIds;

	UPROPERTY(EditAnywhere)
	TArray<int16> UseItemIds;

	// 방어구 추가하면 리스트도 추가
	// + 블루프린트에서 말고 C++ 스크립트에서 할 수 있는 방법없나 확인
};
