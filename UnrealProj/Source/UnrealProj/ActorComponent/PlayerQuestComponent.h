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
	void CheckHuntQuest(int TargetId); // ��� ����Ʈ ����� ���鼭 Ÿ�ٰ� ��ġ�ϴ� ����Ʈ �ֳ� üũ
	void CheckItemQuest(int TargetType, int TargetId); // ������ ����Ʈ ����� ���鼭 Ÿ�ٰ� ��ġ�ϴ� ����Ʈ �ֳ� üũ
	void CheckInvestigateQuest(int TargetId); // ���� ����Ʈ ����� ���鼭 Ÿ�ٰ� ��ġ�ϴ� ����Ʈ �ֳ� üũ
	void CheckETCQuest(int EtcType);// ��Ÿ ����Ʈ ����� ���鼭 Ÿ�ٰ� ��ġ�ϴ� ����Ʈ�� �ֳ� üũ
	
	// �� 4���� �Լ��� �÷��̾ ���͸� ���� ��, �������� ȹ���� ��, ���縦 ������ �� ���� ��Ȳ����
	// ��� ����ǵ��� �Ѵ�. (delegate�� ����ص� ���� �׳� �Լ� ȣ���� �ص� ����)

	void ClearQuest(class UQuest* Quest);
	void OnGoingToCompletable(class UQuest* Quest);
	// �� 4���� �Լ��� ���� ����Ʈ Ÿ�� �ѹ��� �����ϰ� �Ϸ� ������ �޼��ظ� �� �Լ��� �������
	// �Ϸᰡ�� ����Ʈ�� �ٲ��ش�.

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
