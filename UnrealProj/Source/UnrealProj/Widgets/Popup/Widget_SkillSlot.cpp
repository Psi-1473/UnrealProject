// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget_SkillSlot.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "../../Skills/Skill.h"

void UWidget_SkillSlot::SetInfo()
{
	Img_Skill->SetBrushFromTexture(Skill->GetTexture());
	Text_Name->SetText(FText::FromString(*(Skill->GetSkillName())));
}
