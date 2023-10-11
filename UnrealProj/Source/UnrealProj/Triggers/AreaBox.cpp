// Fill out your copyright notice in the Description page of Project Settings.


#include "AreaBox.h"
#include "../Creatures/Player/MyPlayer.h"
#include "../MyGameInstance.h"
#include "../Managers/SoundManager.h"
#include "Components/BoxComponent.h"
#include "../Widgets/Popup/Widget_AreaTitle.h"

// Sets default values
AAreaBox::AAreaBox()
{
	PrimaryActorTick.bCanEverTick = false;
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoxComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AAreaBox::BeginPlay()
{
	Super::BeginPlay();
	SetAreaTypeName();

	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AAreaBox::OnOverlapBegin);
	
}

void AAreaBox::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		auto Player = Cast<AMyPlayer>(OtherActor);
		if (Player)
		{
			if(AreaTypeName.Len() <= 0)
				SetAreaTypeName();
			
			auto GInstance = Cast<UMyGameInstance>(GetGameInstance());
			GInstance->GetSoundMgr()->SetArea(this);
			auto Widget = ShowAreaUI();
			auto TitleWidget = Cast<UWidget_AreaTitle>(Widget);
			TitleWidget->Init(this);
		}
	}
}

void AAreaBox::SetAreaTypeName()
{
	// BP_Area_
	FString ClassName = GetClass()->GetName();
	FString PreName = TEXT("BP_Area_");
	int StartIndex = PreName.Len();
	int Cnt = ClassName.Len() - StartIndex - 2;

	AreaTypeName = ClassName.Mid(StartIndex, Cnt);

}

UUserWidget* AAreaBox::ShowAreaUI()
{
	auto GInstance = Cast<UMyGameInstance>(GetGameInstance());
	return GInstance->GetUIMgr()->PopupUI(GetWorld(), UIType::AreaTitle);
}

