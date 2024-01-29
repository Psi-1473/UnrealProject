// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileManager.h"
#include "GameFramework/Actor.h"
#include "../Projectiles/Projectile.h"

AProjectile* UProjectileManager::FireProjectile(AActor* Owner, TSubclassOf<class AProjectile> Obj, FVector StartLoc, FRotator Rot, float arcValue)
{

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = Owner;
	SpawnParams.Instigator = Owner->GetInstigator();

	AProjectile* Projectile = Owner->GetWorld()->SpawnActor<AProjectile>(Obj, StartLoc, Rot, SpawnParams);
	FVector FireDir = Projectile->GetActorForwardVector() + (FVector::UpVector * arcValue);
	Projectile->FireInDirection(FireDir, 1.f);
	// ��Ÿ ���� ��.. �ӵ��� ������ ���� ��
	return Projectile;
}
