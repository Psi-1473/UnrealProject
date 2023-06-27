// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameMode.h"
#include "Blueprint/UserWidget.h"

AMyGameMode::AMyGameMode()
{
	static ConstructorHelpers::FClassFinder<UUserWidget> UW(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/02_Blueprints/Widget/WBP_Main.WBP_Main_C'"));
	UE_LOG(LogTemp, Warning, TEXT("GameMode Init!"));
	if (UW.Succeeded())
	{
		HUD_Class = UW.Class;

		CurrentWidget = CreateWidget(GetWorld(), HUD_Class);
		if (CurrentWidget)
			CurrentWidget->AddToViewport();
	}
}
