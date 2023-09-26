// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget_NpcInfo.h"
#include "../../Creatures/Npc/Npc.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "../../ActorComponent/QuestComponent.h"

UWidget_NpcInfo::UWidget_NpcInfo(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	static ConstructorHelpers::FObjectFinder<UTexture2D> POSSIBLE(TEXT("/Script/Engine.Texture2D'/Game/09_Image/UI/QuestPossible.QuestPossible'"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> COMPLETABLE(TEXT("/Script/Engine.Texture2D'/Game/09_Image/UI/QuestClear.QuestClear'"));
	if (POSSIBLE.Succeeded()) PossibleMark = POSSIBLE.Object;
	if (COMPLETABLE.Succeeded()) CompletableMark = COMPLETABLE.Object;

}

void UWidget_NpcInfo::BindNpc(ANpc* NpcValue)
{
	Npc = NpcValue;
	Text_Name->SetText(FText::FromString(NpcValue->GetNpcName()));
	Text_Job->SetText(FText::FromString(NpcValue->GetNpcJob()));
	UE_LOG(LogTemp, Warning, TEXT("Npc Info Bind"));
}

void UWidget_NpcInfo::UpdateQuestMark()
{
	int PossibleQuestNum = Npc->GetQuestComponent()->GetPossibleQuestNum();
	int CompletableQuestNum = Npc->GetQuestComponent()->GetCompletableQuestNum();
	if (CompletableQuestNum > 0)
	{
		Img_QuestMark->SetVisibility(ESlateVisibility::Visible);
		// 퀘스트 마크 - 완료가능
		Img_QuestMark->SetBrushFromTexture(CompletableMark);
	}
	else if (PossibleQuestNum > 0)
	{
		Img_QuestMark->SetVisibility(ESlateVisibility::Visible);
		// 퀘스트 마크 - 시작 가능
		Img_QuestMark->SetBrushFromTexture(PossibleMark);
	}
	else
	{
		Img_QuestMark->SetVisibility(ESlateVisibility::Hidden);
		// 퀘스트 마크 지우기

	}
}
