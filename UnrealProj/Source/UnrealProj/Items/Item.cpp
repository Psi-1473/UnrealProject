
#include "Item.h"
#include "Kismet/GameplayStatics.h"
#include "../MyGameInstance.h"
#include "../Creatures/Player/MyPlayer.h"

AItem::AItem()
{
	PrimaryActorTick.bCanEverTick = true;

}
void AItem::BeginPlay()
{
	Super::BeginPlay();
	
}

void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AItem::UseItem()
{
}

void AItem::SetItemMesh(int _Id, WEAPONTYPE _Type)
{
}

FRichImageRow* AItem::GetItemImage(UMyGameInstance* GInstance)
{

	return GInstance->GetUseItemImage(1);
}



