// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget_QuestWindow.h"
#include "Components/Button.h"

void UWidget_QuestWindow::NativeConstruct()
{
	Super::NativeConstruct();
	Btn_Minimization->OnClicked.AddDynamic(this, &UWidget_QuestWindow::MinimizationWindow);
}

void UWidget_QuestWindow::MinimizationWindow()
{
	UE_LOG(LogTemp, Warning, TEXT("BTN CLICKED!"));
}
