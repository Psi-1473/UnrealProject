// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget_Skill.h"
#include "Kismet/GameplayStatics.h"
#include "../../Creatures/Player/MyPlayer.h"
#include "../../Skills/Components/PlayerSkillComponent.h"
#include "../../Skills/Skill.h"
#include "../../Skills/Player/PlayerSkill.h"
#include "Widget_SkillSlot.h"
#include "Components/ScrollBox.h"

UWidget_Skill::UWidget_Skill(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	static ConstructorHelpers::FClassFinder<UUserWidget> SA(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/02_Blueprints/Widget/Slots/WBP_SkillSlot.WBP_SkillSlot_C'"));
	if (SA.Succeeded()) BP_Slot = SA.Class;
}
void UWidget_Skill::NativeConstruct()
{
	Super::NativeConstruct();
	CreateSlot();
}

void UWidget_Skill::CreateSlot()
{
	auto Char = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	auto MyPlayer = Cast<AMyPlayer>(Char);

	int Number = MyPlayer->GetSkillComponent()->GetSkillNumber();

	for (int i = 0; i < Number; i++)
	{
		Slot = CreateWidget(GetWorld(), BP_Slot);
		SkillSlot->AddChild(Slot);
		UWidget_SkillSlot* WSlot = Cast<UWidget_SkillSlot>(Slot);
		WSlot->SetSkill(MyPlayer->GetSkillComponent()->GetSkills()[i]);
		WSlot->SetInfo();
	}

}
