// Fill out your copyright notice in the Description page of Project Settings.


#include "UIManager.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/PlayerController.h"

UIManager::UIManager()
{
	PopupUiArray.Init(nullptr, (int)UIType::End);
}

UIManager::~UIManager()
{
	PopupUiArray.Empty();
}

UUserWidget* UIManager::PopupUI(UWorld* World, UIType Type)
{
	if (PopupUiArray[(int)Type] != nullptr)
	{
		if (Type == UIType::Inventory || Type == UIType::Skill) 
			CloseUI((int)UIType::Information);
		CloseUI((int)Type);
		return nullptr;
	}

	const UEnum* UIEnum = FindFirstObjectSafe<UEnum>(TEXT("UIType"));
	if (UIEnum == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Enum Pointer NULL"));
		return nullptr;
	}

	FString UIName = UIEnum->GetNameStringByValue((int64)Type);
	FString BPName = TEXT("WBP_") + UIName;
	FString Dir = TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/02_Blueprints/Widget/Popup/");
	Dir += BPName + TEXT(".") + BPName + TEXT("_C'");

	WidgetAsset = LoadClass<UUserWidget>(NULL, *Dir, NULL, LOAD_None, NULL);
	UUserWidget* PopupUi;
	PopupUi = CreateWidget(World, WidgetAsset);
	PopupUi->AddToViewport();
	PopupUiArray[(int)Type] = PopupUi;

	if(Type != UIType::BossHpBar)
		UiNumber++;

	if (UiNumber == 1)
	{
		auto PC = Cast<APlayerController>(PlayerController);
		PC->SetInputMode(FInputModeGameAndUI());
		PC->bShowMouseCursor = true;
	}

	return PopupUi;
}

void UIManager::CloseUI(int Type)
{
	if(PopupUiArray[Type] == nullptr)
		return;

	PopupUiArray[Type]->Destruct();
	PopupUiArray[Type]->RemoveFromViewport();
	PopupUiArray[Type] = nullptr;

	if (Type != (int)UIType::BossHpBar)
		UiNumber--;

	if (UiNumber <= 0)
	{
		UiNumber = 0;
		auto PC = Cast<APlayerController>(PlayerController);
		PC->SetInputMode(FInputModeGameOnly());
		PC->bShowMouseCursor = false;
	}

}

void UIManager::CloseAllUI()
{
	int Cnt = (int)UIType::End;

	for (int i = 0; i < Cnt; i++)
		CloseUI(i);
}
