// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"
#include "Components/StaticMeshComponent.h"
#include "../../Projectiles/Projectile.h"

AWeapon::AWeapon()
{
	static ConstructorHelpers::FClassFinder<AProjectile> ARROW(TEXT("/Script/Engine.Blueprint'/Game/02_Blueprints/Projectiles/BP_Arrow.BP_Arrow_C'"));
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

	if (ARROW.Succeeded())
		Arrow = ARROW.Class;
}

void AWeapon::Init(WEAPONTYPE _Type, int _Id)
{
	Type = _Type;
	Id = _Id;
	
	if (Type == WEAPON_ARROW)
		bRight = false;

	FString TypeString = FString::FromInt(_Type);
	FString IdString = FString::FromInt(Id);
	FString Directory = TEXT("/Script/Engine.StaticMesh'/Game/04_Mesh/Weapon/");
	Directory += TypeString + TEXT("/") + IdString + TEXT(".") + IdString + TEXT("'");

	StaticMesh = LoadObject<UStaticMesh>(NULL, *Directory, NULL, LOAD_None, NULL);
	StaticMeshComponent->SetStaticMesh(StaticMesh);
}