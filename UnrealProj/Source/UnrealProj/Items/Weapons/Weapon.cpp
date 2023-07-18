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

void AWeapon::UseItem()
{
	// 아이템 장착 구현
	UE_LOG(LogTemp, Warning, TEXT("Weapon Equip"));
	auto Player = Inventory->GetPlayer();

	auto EquipedWeapon = Player->GetWeapon();
	Player->EquipWeapon(this);
	Inventory->EmptySlot(Inventory->GetWeaponItems(), SlotIndex);
	// 변경해야함 여기 에러남 무기 바꿔끼면
	// 1. 장착하려는 아이템 자리 비움
	// 2. 기존에 장착하던 아이템을 그 자리에 채움
	// 3. 장착한 장비 바꿈
	// 여기서 1~2번이 안된다.
	ItemType IType;
	if (EquipedWeapon->GetType() == WEAPONTYPE::WEAPON_SWORD) IType = ITEM_SWORD;
	else if (EquipedWeapon->GetType() == WEAPONTYPE::WEAPON_ARROW) IType = ITEM_BOW;
	Inventory->GainNewItem(IType, EquipedWeapon->GetId(), SlotIndex);
	// 여기까지
	if (Player->GetWeapon()->GetType() == WEAPONTYPE::WEAPON_SWORD)
		UE_LOG(LogTemp, Warning, TEXT("Sword EQUIP!"));
	if (Player->GetWeapon()->GetType() == WEAPONTYPE::WEAPON_ARROW)
		UE_LOG(LogTemp, Warning, TEXT("Bow EQUIP!"));
}

void AWeapon::SetItemMesh()
{
	Super::SetItemMesh();
	if (Type == WEAPONTYPE::WEAPON_ARROW)
		bRight = false;

	FString TypeString = FString::FromInt((int)Type);
	FString IdString = FString::FromInt(Id);
	FString Directory = TEXT("/Script/Engine.StaticMesh'/Game/04_Mesh/Weapon/");
	Directory += TypeString + TEXT("/") + IdString + TEXT(".") + IdString + TEXT("'");

	StaticMesh = LoadObject<UStaticMesh>(NULL, *Directory, NULL, LOAD_None, NULL);
	StaticMeshComponent->SetStaticMesh(StaticMesh);
}

void AWeapon::SetCount(int Value)
{
}

FRichImageRow* AWeapon::GetItemImage(UMyGameInstance* GInstance)
{
	switch (Type)
	{
	case WEAPONTYPE::WEAPON_SWORD:
		UE_LOG(LogTemp, Warning, TEXT("SWORD IMAGE LOAD"));
		return GInstance->GetSwordImage(Id);
		break;
	case WEAPONTYPE::WEAPON_ARROW:
		UE_LOG(LogTemp, Warning, TEXT("BOW IMAGE LOAD"));
		return GInstance->GetBowImage(Id);
		break;
	default:
		return nullptr;
		break;
	}
}

