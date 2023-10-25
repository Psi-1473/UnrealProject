// Fill out your copyright notice in the Description page of Project Settings.


#include "UIManager.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/PlayerController.h"
#include "Sound/SoundWave.h"
#include "SoundManager.h"
#include "../MyGameInstance.h"

UIManager::UIManager()
{
	static ConstructorHelpers::FObjectFinder<USoundWave> PopupSound(TEXT("/Script/Engine.SoundWave'/Game/10_Sound/Sound/UI/Sound_UI_Popup.Sound_UI_Popup'"));
	static ConstructorHelpers::FObjectFinder<USoundWave> CloseSound(TEXT("/Script/Engine.SoundWave'/Game/10_Sound/Sound/UI/Sound_UI_Close.Sound_UI_Close'"));
	static ConstructorHelpers::FObjectFinder<USoundWave> ButtonSound(TEXT("/Script/Engine.SoundWave'/Game/10_Sound/Sound/UI/Sound_UI_Button.Sound_UI_Button'"));

	if (PopupSound.Succeeded()) Sound_Popup = PopupSound.Object;
	if (CloseSound.Succeeded()) Sound_Close = CloseSound.Object;
	if (ButtonSound.Succeeded()) Sound_Button = ButtonSound.Object;

	PopupUiArray.Init(nullptr, (int)UIType::End);
}

UIManager::~UIManager()
{
	PopupUiArray.Empty();
}

UUserWidget* UIManager::PopupUI(UWorld* World, UIType Type)
{
	// 1. 이미 UI가 열려있는 경우엔 닫는다.
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

	if(Type == UIType::AreaTitle)
		CloseUI((int)Type);

	if (Type != UIType::BossHpBar && Type != UIType::QuestQuickInfo 
	&& Type != UIType::Information && Type != UIType::AreaTitle)
	{
		UiNumber++;
		USoundManager::PlaySound(PlayerController->GetWorld(), Sound_Popup);
	}

	// 2. 각종 예외처리를 거친 후 Enum 값을 String으로 변환
	// 3. UI블루프린트가 모여있는 디렉토리에 접근해 String으로 변환한 Enum과 일치하는 위젯을 메모리로 가져온다
	// 4. 메모리에 올린 UI 데이터를 화면에 띄운다.
	FString UIName = UIEnum->GetNameStringByValue((int64)Type);
	FString BPName = TEXT("WBP_") + UIName;
	FString Dir = TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/02_Blueprints/Widget/Popup/");
	Dir += BPName + TEXT(".") + BPName + TEXT("_C'");

	WidgetAsset = LoadClass<UUserWidget>(NULL, *Dir, NULL, LOAD_None, NULL);
	UUserWidget* PopupUi;
	PopupUi = CreateWidget(World, WidgetAsset);
	PopupUi->AddToViewport();
	PopupUiArray[(int)Type] = PopupUi;



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
	
	if (Type != (int)UIType::BossHpBar && Type != (int)UIType::QuestQuickInfo 
	&& Type != (int)UIType::Information && Type != (int)UIType::AreaTitle)
	{
		USoundManager::PlaySound(PlayerController->GetWorld(), Sound_Close);
		UiNumber--;
	}

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

void UIManager::PlayButtonSound()
{
	USoundManager::PlaySound(PlayerController->GetWorld(), Sound_Button);
}
