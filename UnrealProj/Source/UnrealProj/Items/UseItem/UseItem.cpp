// Fill out your copyright notice in the Description page of Project Settings.


#include "UseItem.h"
#include "../../MyGameInstance.h"
#include "Components/StaticMeshComponent.h"
#include "../../Creatures/Player/MyPlayer.h"
#include "GameFramework/Actor.h"
#include "../../Projectiles/Projectile.h"
#include "Kismet/GameplayStatics.h"
#include "../../Inventory/Inventory.h"
#include "../../MyGameMode.h"
#include "../../Widgets/Widget_PlayerMain.h"
#include "../../Widgets/Popup/Widget_Inventory.h"
#include "../../Creatures/Player/MyPlayer.h"
#include "../../Stat/PlayerStatComponent.h"
#include "Sound/SoundWave.h"


AUseItem::AUseItem()
{
	static ConstructorHelpers::FObjectFinder<USoundWave> UseSound(TEXT("/Script/Engine.SoundWave'/Game/10_Sound/Sound/Sound_UI_PotionUse.Sound_UI_PotionUse'"));

	if (UseSound.Succeeded()) Sound_Use = UseSound.Object;
}

void AUseItem::UseItem()
{
	UE_LOG(LogTemp, Warning, TEXT("Item Use %d, %d"), UseType, Amount);

	auto MyPlayer = Cast<AMyPlayer>(Owner);
	SetCount(Count - 1);

	UGameplayStatics::PlaySound2D(MyPlayer->GetWorld(), Sound_Use);
	
	switch (UseType)
	{
		case 0:
			MyPlayer->GetStatComponent()->AddHp(Amount);
			break;
		case 1:
			MyPlayer->GetStatComponent()->AddMp(Amount);
			break;
		default:
			break;
	}
}

void AUseItem::SetItemMesh()
{
	Super::SetItemMesh();

}

void AUseItem::SetCount(int Value)
{
	Super::SetCount(Value);
	Count = Value;
	auto GInstance = Cast<UMyGameInstance>(Inventory->GetPlayer()->GetInstance());
	auto Inven = GInstance->GetUIMgr()->GetUI(UIType::Inventory);

	UWorld* Wolrd = Inventory->GetPlayer()->GetWorld();
	auto GMode = UGameplayStatics::GetGameMode(Wolrd);
	auto GameMode = Cast<AMyGameMode>(GMode);
	if (GameMode == nullptr) return;
	auto Widget = Cast<UWidget_PlayerMain>(GameMode->GetCurrentWidget());
	if (Widget == nullptr) return;

	if (Count == 0)
	{
		Inventory->EmptySlot(Inventory->GetUseItems(), SlotIndex);
		if (QuickSlotIndex != -1)
			Widget->EmptyItemSlot(QuickSlotIndex);
	}

	if (QuickSlotIndex != -1)
		Widget->RefreshItemQuickSlot(QuickSlotIndex);

	if (Inven != nullptr)
	{
		auto InvenWidget = Cast<UWidget_Inventory>(Inven);
		InvenWidget->RefreshSlotByIndex(SlotIndex);
	}
}

void AUseItem::LoadItemData(UMyGameInstance* GInstance)
{
	UseType = GInstance->GetUseItemData(Id)->Type;
	Amount = GInstance->GetUseItemData(Id)->Amount;
}


FRichImageRow* AUseItem::GetItemImage(UMyGameInstance* GInstance)
{
	return GInstance->GetUseItemImage(Id);
}


