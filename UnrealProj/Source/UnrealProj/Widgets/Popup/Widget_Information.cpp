// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget_Information.h"
#include "../../MyGameInstance.h"

void UWidget_Information::SetInfo(InformationType Type, int Id)
{
	FString Name;
	FString Sub;

	// GInstance ��������
	if (Type == INFO_ITEM)
	{
		// Name = GInstance�� ���� �ҷ��� ������ �������� Name
		// Sub = GInstance�� ���� �ҷ��� ������ �������� Sub
	}
	else if (Type == INFO_SKILL)
	{
		// �˽�ų���� Ȱ��ų���� Ȯ���ʿ��ҵ�
	}
}
