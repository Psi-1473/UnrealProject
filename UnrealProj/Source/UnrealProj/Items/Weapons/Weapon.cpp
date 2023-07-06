// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"
#include "Components/StaticMeshComponent.h"
#include "../../MyGameInstance.h"
#include "../../Creatures/Player/MyPlayer.h"
#include "../../MyGameInstance.h"
#include "../../Projectiles/Projectile.h"
#include "../../Inventory/Inventory.h"

AWeapon::AWeapon()
{
	static ConstructorHelpers::FClassFinder<AProjectile> ARROW(TEXT("/Script/Engine.Blueprint'/Game/02_Blueprints/Projectiles/BP_Arrow.BP_Arrow_C'"));
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

	if (ARROW.Succeeded())
		Arrow = ARROW.Class;
}

void AWeapon::UseItem(int SlotNumber)
{
	// 아이템 장착 구현
	UE_LOG(LogTemp, Warning, TEXT("Weapon Equip"));
	auto Player = Inventory->GetPlayer();

	auto EquipedWeapon = Player->GetWeapon();
	Player->EquipWeapon(this);
	Inventory->RemoveWeapon(SlotNumber);
	Inventory->GainNewItem(EquipedWeapon, SlotNumber);

	if (Player->GetWeapon()->GetType() == WEAPON_SWORD)
		UE_LOG(LogTemp, Warning, TEXT("Sword EQUIP!"));
	if (Player->GetWeapon()->GetType() == WEAPON_ARROW)
		UE_LOG(LogTemp, Warning, TEXT("Bow EQUIP!"));
}

void AWeapon::SetItemMesh()
{
	Super::SetItemMesh();
	if (Type == WEAPON_ARROW)
		bRight = false;

	FString TypeString = FString::FromInt(Type);
	FString IdString = FString::FromInt(Id);
	FString Directory = TEXT("/Script/Engine.StaticMesh'/Game/04_Mesh/Weapon/");
	Directory += TypeString + TEXT("/") + IdString + TEXT(".") + IdString + TEXT("'");

	StaticMesh = LoadObject<UStaticMesh>(NULL, *Directory, NULL, LOAD_None, NULL);
	StaticMeshComponent->SetStaticMesh(StaticMesh);
}

FRichImageRow* AWeapon::GetItemImage(UMyGameInstance* GInstance)
{
	switch (Type)
	{
	case WEAPON_SWORD:
		UE_LOG(LogTemp, Warning, TEXT("SWORD IMAGE LOAD"));
		return GInstance->GetSwordImage(Id);
		break;
	case WEAPON_ARROW:
		UE_LOG(LogTemp, Warning, TEXT("BOW IMAGE LOAD"));
		return GInstance->GetBowImage(Id);
		break;
	default:
		return nullptr;
		break;
	}
}

