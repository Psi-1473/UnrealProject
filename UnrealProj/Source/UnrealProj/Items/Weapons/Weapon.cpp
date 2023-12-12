// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"
#include "Components/StaticMeshComponent.h"
#include "../../MyGameInstance.h"
#include "../../Creatures/Player/MyPlayer.h"
#include "../../Animations/Player/PlayerAnim.h"
#include "../../MyGameInstance.h"
#include "../../Projectiles/Projectile.h"
#include "../../Projectiles/Player/Arrow.h"
#include "../../Inventory/Inventory.h"
#include "../../Skills/Player/PlayerSkill.h"
#include "../../State/CharacterState.h"
#include "Sound/SoundWave.h"

AWeapon::AWeapon()
{
	static ConstructorHelpers::FClassFinder<AProjectile> ARROW(TEXT("/Script/Engine.Blueprint'/Game/02_Blueprints/Projectiles/BP_Arrow.BP_Arrow_C'"));
	static ConstructorHelpers::FObjectFinder<USoundWave> SHitSound(TEXT("/Script/Engine.SoundWave'/Game/10_Sound/Sound/Player/Sword/Sound_Player_SwordHit.Sound_Player_SwordHit'"));
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

	if (ARROW.Succeeded()) Arrow = ARROW.Class;
	if (SHitSound.Succeeded()) SwordHitSound = SHitSound.Object;

}

void AWeapon::UseItem()
{
	// 아이템 장착 구현
	UE_LOG(LogTemp, Warning, TEXT("Weapon Equip"));
	auto Player = Inventory->GetPlayer();
	auto EquipedWeapon = Player->GetWeapon();
	Player->EquipWeapon(this);
	Inventory->EmptySlot(Inventory->GetWeaponItems(), SlotIndex);
	// 변경해야함 여기
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

void AWeapon::OnLeftMouseClicked(AMyPlayer* Player)
{
	if (Player->GetState() != Player->GetSpecificState(STATE::IDLE) &&
		Player->GetState() != Player->GetSpecificState(STATE::MOVE) &&
		Player->GetState() != Player->GetSpecificState(STATE::JUMP) &&
		Player->GetState() != Player->GetSpecificState(STATE::ATTACK) &&
		Player->GetState() != Player->GetSpecificState(STATE::SKILLCAST))
		return;

	if (Player->GetState() == Player->GetSpecificState(STATE::SKILL))
		return;

	if (Player->GetState() == Player->GetSpecificState(STATE::SKILLCAST))
		Player->GetSkill()->CastToExecute(Player);
	else
	{
		if (Player->GetState() != Player->GetSpecificState(STATE::ATTACK))
			Player->SetState(STATE::ATTACK);

		Player->GetAnimInst()->PlayAttackMontage();
	}
}

void AWeapon::OnRightMouseClicked(AMyPlayer* Player)
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

