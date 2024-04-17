// Fill out your copyright notice in the Description page of Project Settings.


#include "VehicleInfo.h"
#include "../../MyGameInstance.h"
#include "../Player/MyPlayer.h"

void UVehicleInfo::Init(int VehicleId, TWeakObjectPtr<AMyPlayer> Player)
{
	OwnerPlayer = Player;
	Id = VehicleId;

	// TODO) ������ �ҷ��ͼ� Speed �����ϱ�
	auto Data = OwnerPlayer->GetInstance()->GetVehicleData(Id);

	DashSpeed = Data->DashSpeed;
	Speed = Data->Speed;
	Name = Data->Name;
	Explanation = Data->Explanation;


	Dir = TEXT("/Script/Engine.Blueprint'/Game/02_Blueprints/Creatures/Vehicles/Horse/BP_Horse");
	Dir += FString::FromInt(Id);
	Dir += TEXT(".BP_Horse");
	Dir += FString::FromInt(Id);
	Dir += TEXT("_C'");


}
