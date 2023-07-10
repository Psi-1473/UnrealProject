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

AUseItem::AUseItem()
{
}

void AUseItem::UseItem()
{
	UE_LOG(LogTemp, Warning, TEXT("Item Use"));
	SetCount(Count - 1);
}

void AUseItem::SetItemMesh()
{
	Super::SetItemMesh();
	// ½ºÅÂÆ½ ¸Å½Ã ¼³Á¤

	//FString IdString = FString::FromInt(Id);
	//FString Directory = TEXT("/Script/Engine.StaticMesh'/Game/04_Mesh/Weapon/");
	//Directory += TypeString + TEXT("/") + IdString + TEXT(".") + IdString + TEXT("'");
	//
	//StaticMesh = LoadObject<UStaticMesh>(NULL, *Directory, NULL, LOAD_None, NULL);
	//StaticMeshComponent->SetStaticMesh(StaticMesh);
}

void AUseItem::SetCount(int Value)
{
	Super::SetCount(Value);
	Count = Value;
	if (Count == 0)
	{
		Inventory->EmptySlot(Inventory->GetUseItems(), SlotIndex);
		// Äü½½·Ôµµ 
		UWorld* Wolrd = Inventory->GetPlayer()->GetWorld();
		auto GMode = UGameplayStatics::GetGameMode(Wolrd);
		auto GameMode = Cast<AMyGameMode>(GMode);

		if (GameMode == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("GAME MODE NULL"));
			return;
		}

		auto Widget = Cast<UWidget_PlayerMain>(GameMode->GetCurrentWidget());

		if (Widget == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("WIDGET NULL"));
			return;
		}

		Widget->EmptyItemSlot(QuickSlotIndex);

	}
}

FRichImageRow* AUseItem::GetItemImage(UMyGameInstance* GInstance)
{
	return GInstance->GetUseItemImage(Id);
}


