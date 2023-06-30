
#include "Item.h"


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

FRichImageRow* AItem::GetItemImage()
{
	return nullptr;
}



