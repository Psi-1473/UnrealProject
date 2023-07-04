// Fill out your copyright notice in the Description page of Project Settings.


#include "UseItem.h"
#include "../../MyGameInstance.h"
#include "Components/StaticMeshComponent.h"
#include "../../Creatures/Player/MyPlayer.h"
#include "GameFramework/Actor.h"
#include "../../Projectiles/Projectile.h"
#include "Kismet/GameplayStatics.h"

AUseItem::AUseItem()
{
}

void AUseItem::UseItem()
{
}

void AUseItem::SetItemMesh(int _Id, WEAPONTYPE _Type)
{
	Super::SetItemMesh(_Id, _Type);
	// 스태틱 매시 설정

	//FString IdString = FString::FromInt(Id);
	//FString Directory = TEXT("/Script/Engine.StaticMesh'/Game/04_Mesh/Weapon/");
	//Directory += TypeString + TEXT("/") + IdString + TEXT(".") + IdString + TEXT("'");
	//
	//StaticMesh = LoadObject<UStaticMesh>(NULL, *Directory, NULL, LOAD_None, NULL);
	//StaticMeshComponent->SetStaticMesh(StaticMesh);
}

FRichImageRow* AUseItem::GetItemImage(UMyGameInstance* GInstance)
{

	return GInstance->GetUseItemImage(1);
}


