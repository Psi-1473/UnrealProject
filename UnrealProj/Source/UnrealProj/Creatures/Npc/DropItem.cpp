// Fill out your copyright notice in the Description page of Project Settings.


#include "DropItem.h"
#include "../../Managers/ResourceManager.h"
#include "../../Managers/UIManager.h"
#include "../../MyGameInstance.h"
#include "../Player/MyPlayer.h"
#include "../../State/StateMachine.h"
#include "../../Widgets/Popup/Widget_ItemDrop.h"


void ADropItem::Interact(AMyPlayer* Player)
{
	//Player->GetInstance()->GetResourceMgr()->Destroy<ADropItem>(this);
	auto Widget = Player->GetInstance()->GetUIMgr()->PopupUI(Player->GetWorld(), UIType::ItemDrop);

	if(Widget != nullptr)
	{
		auto ItemDropWidget = Cast<UWidget_ItemDrop>(Widget);
		ItemDropWidget->CreateSlot(MiscItems);
		ItemDropWidget->SetDropItem(this);
		Player->GetStateMachine()->SetState(STATE::INTERACT);	
	}
	else
		Player->GetStateMachine()->SetState(STATE::IDLE);

}
