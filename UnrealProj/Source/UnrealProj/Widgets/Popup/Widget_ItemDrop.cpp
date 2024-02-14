// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget_ItemDrop.h"
#include "Components/ScrollBox.h"
#include "../Widget_DroppedItemSlot.h"
#include "../../MyGameInstance.h"

UWidget_ItemDrop::UWidget_ItemDrop(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	static ConstructorHelpers::FClassFinder<UUserWidget> SLOT(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/02_Blueprints/Widget/Slots/WBP_DroppedItemSlot.WBP_DroppedItemSlot_C'"));
	if (SLOT.Succeeded()) BP_Slot = SLOT.Class;
}

void UWidget_ItemDrop::CreateSlot(TArray<FMiscItemData*> MiscItems)
{
	for (int i = 0; i < MiscItems.Num(); i++)
	{
		UUserWidget* NewSlot = CreateWidget(GetWorld(), BP_Slot);
		ScrollBox_ItemList->AddChild(NewSlot);
		UWidget_DroppedItemSlot* DSlot = Cast<UWidget_DroppedItemSlot>(NewSlot);
		DSlot->SetInfo(MiscItems[i]);
		//QSlot->SetInfo(this, QuestComponent->GetCompletableQuests()[i]);
	}
}
