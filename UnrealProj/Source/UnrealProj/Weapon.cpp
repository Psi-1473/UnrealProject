// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"

UWeapon::UWeapon()
{
}

void UWeapon::Init(WEAPONTYPE _Type, int _Id)
{
	Type = _Type;
	Id = _Id;
	if(Type == WEAPON_SWORD)
		SocketName = TEXT("WEAPON_R");
	else if(Type == WEAPON_ARROW)
		SocketName = TEXT("WEAPON_L");

	FString TypeString = FString::FromInt(_Type);
	FString IdString = FString::FromInt(Id);
	FString Directory = TEXT("/Script/Engine.StaticMesh'/Game/04_Mesh/Weapon/");
	Directory += TypeString + TEXT("/") + IdString + TEXT(".") + IdString + TEXT("'");

	UE_LOG(LogTemp, Warning, TEXT("%s"), *SocketName);
	StaticMesh = LoadObject<UStaticMesh>(NULL, *Directory, NULL, LOAD_None, NULL);
}