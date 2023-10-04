// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget_Skill.h"
#include "Kismet/GameplayStatics.h"
#include "../../Creatures/Player/MyPlayer.h"
#include "../../Skills/Components/PlayerSkillComponent.h"
#include "../../Skills/Skill.h"
#include "../../Skills/Player/PlayerSkill.h"
#include "Widget_SkillSlot.h"
#include "Components/HorizontalBox.h"
#include "Components/Button.h"

UWidget_Skill::UWidget_Skill(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	static ConstructorHelpers::FClassFinder<UUserWidget> SWORDSKILL(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/02_Blueprints/Widget/Popup/WBP_SkilSword.WBP_SkilSword_C'"));
	static ConstructorHelpers::FClassFinder<UUserWidget> BOWSKILL(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/02_Blueprints/Widget/Popup/WBP_SkillBow.WBP_SkillBow_C'"));
	if (SWORDSKILL.Succeeded()) BP_SwordSkill = SWORDSKILL.Class;
	if (BOWSKILL.Succeeded()) BP_BowSkill = BOWSKILL.Class;
}
void UWidget_Skill::NativeConstruct()
{
	Super::NativeConstruct();
	SetSwordSkill();
	Btn_Sword->OnClicked.AddDynamic(this, &UWidget_Skill::SetSwordSkill);
	Btn_Bow->OnClicked.AddDynamic(this, &UWidget_Skill::SetBowSkill);
}

void UWidget_Skill::SetSwordSkill()
{
	WidgetBox->ClearChildren();
	UUserWidget* NowSkill = CreateWidget(GetWorld(), BP_SwordSkill);

	WidgetBox->AddChild(NowSkill);
}

void UWidget_Skill::SetBowSkill()
{
	WidgetBox->ClearChildren();
	UUserWidget* NowSkill = CreateWidget(GetWorld(), BP_BowSkill);

	WidgetBox->AddChild(NowSkill);
}
