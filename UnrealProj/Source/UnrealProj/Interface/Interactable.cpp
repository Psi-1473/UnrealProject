// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactable.h"
#include "../Creatures/Player/MyPlayer.h"

// Add default functionality here for any IInteractable functions that are not pure virtual.

void IInteractable::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		auto Player = Cast<AMyPlayer>(OtherActor);
		if (Player)
		{
			Player->SetInteractObj(Cast<AActor>(this->_getUObject()));
			UE_LOG(LogTemp, Warning, TEXT("Player Enter!"));
		}
		
	}
}

void IInteractable::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor)
	{
		auto Player = Cast<AMyPlayer>(OtherActor);
		if (Player)
		{
			Player->SetInteractObj(nullptr);
			UE_LOG(LogTemp, Warning, TEXT("Player Out!"));
		}
	}
}
