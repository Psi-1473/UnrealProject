// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget_InvenSlot.h"
#include "Components/RichTextBlockImageDecorator.h"
#include "../../Items/Item.h"
#include "../../Items/Weapons/Weapon.h"
#include "../../Items/UseItem/UseItem.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

#include "../../MyGameInstance.h"
#include "Kismet/GameplayStatics.h"

void UWidget_InvenSlot::NativeConstruct()
{
}

void UWidget_InvenSlot::SetImage()
{
	if (SlotItem == nullptr) return;
	
	auto GInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	//Img_Item->SetBrush(GInstance->GetUseItemImage(1)->Brush);
	// 주석처리한 얘네는 실행된다.
	Img_Item->SetBrush(SlotItem->GetItemImage(GInstance)->Brush);
} 

void UWidget_InvenSlot::SetCount()
{
	if (SlotItem == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("NULL SLOT"));
		Text_Count->SetText(FText::FromString(TEXT("")));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("NOT NULL SLOT"));
		FString Cnt = FString::FromInt(SlotItem->GetCount());
		Text_Count->SetText(FText::FromString(Cnt));
	}
}
