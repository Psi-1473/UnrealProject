// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerQuestComponent.generated.h"

USTRUCT()
struct FQuestIndexData
{
	GENERATED_BODY()
public:
	int32 NpcId;
	int32 QuestId;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREALPROJ_API UPlayerQuestComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UPlayerQuestComponent();

protected:
	virtual void BeginPlay() override;

public:
	TArray<class UQuest*> GetOnGoingQuests() { return OnGoingQuests; }
	TArray<class UQuest*> GetCompletableQuests() { return CompletableQuests; }

public:
	void TakeNewQuest(class ANpc* Npc, int32 QuestId);
	
	void CheckQuest(int QuestType, int TargetId, int TargetType);
	void CheckHuntQuest(int TargetId); // 사냥 퀘스트 목록을 돌면서 타겟과 일치하는 퀘스트 있나 체크
	void CheckItemQuest(int TargetType, int TargetId); // 아이템 퀘스트 목록을 돌면서 타겟과 일치하는 퀘스트 있나 체크
	void CheckInvestigateQuest(int TargetId); // 조사 퀘스트 목록을 돌면서 타겟과 일치하는 퀘스트 있나 체크
	void CheckETCQuest(int EtcType);// 기타 퀘스트 목록을 돌면서 타겟과 일치하는 퀘스트가 있나 체크
	
	// 위 4개의 함수는 플레이어가 몬스터를 잡을 때, 아이템을 획득할 때, 조사를 진행할 때 등의 상황에서
	// 계속 실행되도록 한다. (delegate를 사용해도 좋고 그냥 함수 호출을 해도 좋음)

	void ClearQuest(class UQuest* Quest);
	void OnGoingToCompletable(class UQuest* Quest);
	// 위 4개의 함수를 통해 퀘스트 타겟 넘버를 갱신하고 완료 조건을 달성해면 이 함수를 실행시켜
	// 완료가능 퀘스트로 바꿔준다.

	bool AdddToBindedQuest(class UQuest* Quest);
	void RemoveBindedQuest(class UQuest* Quest) {BindedQuest.Remove(Quest);}
private:
	class UQuest* CreateNewQuest(struct FQuestData* QuestData);

private:
	UPROPERTY()
	TArray<class UQuest*> OnGoingQuests;

	UPROPERTY()
	TArray<class UQuest*> HuntQuests;

	UPROPERTY()
	TArray<class UQuest*> ItemQuests;

	UPROPERTY()
	TArray<class UQuest*> EtcQuests;

	UPROPERTY()
	TArray<class UQuest*> InvestigateQuests;

	UPROPERTY()
	TArray<class UQuest*> CompletableQuests;

	UPROPERTY()
	TArray<FQuestIndexData> CompletedQuests;

	UPROPERTY()
	TArray<class UQuest*> BindedQuest;

		
};
