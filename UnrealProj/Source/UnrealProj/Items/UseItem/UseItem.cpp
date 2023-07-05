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

void AUseItem::UseItem(int SlotNumber)
{
	UE_LOG(LogTemp, Warning, TEXT("Item Use"));
}

void AUseItem::SetItemMesh()
{
	Super::SetItemMesh();
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
	return GInstance->GetUseItemImage(Id);
}


