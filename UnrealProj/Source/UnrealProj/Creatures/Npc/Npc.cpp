// Fill out your copyright notice in the Description page of Project Settings.


#include "Npc.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "../Player/MyPlayer.h"
#include "Kismet/GameplayStatics.h"
#include "../../MyGameInstance.h"
#include "../../Widgets/Popup/Widget_Script.h"
#include "../../ActorComponent/QuestComponent.h"
#include "../../Managers/QuestManager.h"
#include "Components/WidgetComponent.h"
#include "PaperSpriteComponent.h"
#include "PaperSprite.h"
#include "../../Widgets/Components/Widget_NpcInfo.h"

ANpc::ANpc()
{
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	MinimapIcon = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("MinimapIcon"));
	InteractBox = CreateDefaultSubobject<UBoxComponent>(TEXT("InteractBox"));
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	QuestComponent = CreateDefaultSubobject<UQuestComponent>(TEXT("QuestComponent"));
	NpcInfo = CreateDefaultSubobject<UWidgetComponent>(TEXT("NpcInfo")); 
	static ConstructorHelpers::FClassFinder<UUserWidget> WNpc(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/02_Blueprints/Widget/Components/WBP_NpcInfo.WBP_NpcInfo_C'"));

	if (WNpc.Succeeded())
		NpcInfo->SetWidgetClass(WNpc.Class);

	NpcInfo->SetWidgetSpace(EWidgetSpace::Screen);
	Mesh->SetRelativeLocation(FVector(0.f, 0.f, -88.f));
	Mesh->SetRelativeRotation(FRotator(0.f, -90.f, -0.f));
	//MinimapIcon->SetRelativeLocation(FVector(0.f, 0.f, 1000.f));
	MinimapIcon->SetWorldRotation(FRotator(0.f, 90.f, -90.f));
	MinimapIcon->bVisibleInSceneCaptureOnly = true;
	MinimapIcon->SetCollisionProfileName(TEXT("NoCollision"));
	InteractBox->SetRelativeScale3D(FVector(3.f, 3.f, 3.f));
	InteractBox->SetCollisionProfileName("InteractBox");

	CapsuleComponent->SetCapsuleHalfHeight(88.f);
	CapsuleComponent->SetCapsuleRadius(34.f);

	RootComponent = CapsuleComponent;
	InteractBox->SetupAttachment(RootComponent);
	Mesh->SetupAttachment(RootComponent);
	NpcInfo->SetupAttachment(RootComponent);
	//MinimapIcon->SetupAttachment(RootComponent);
	// 박스 사이즈 조절

	InteractBox->OnComponentBeginOverlap.AddDynamic(this, &IInteractable::OnOverlapBegin);
	InteractBox->OnComponentEndOverlap.AddDynamic(this, &IInteractable::OnOverlapEnd);
}

void ANpc::PostInitializeComponents()
{
	Super::PostInitializeComponents();

}

void ANpc::BeginPlay()
{
	AActor::BeginPlay();
	SetNpcInfo();
	SetPlayer();

	MinimapIcon->SetWorldLocation(GetActorLocation() + GetActorUpVector() * 1000.f);
	LoadPossibleQuestData(Cast<AMyPlayer>(MainPlayer));
	NpcInfo->InitWidget();
}

void ANpc::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	SetVisiblityInfoWidget();
}

UPaperSprite* ANpc::GetSprite(FString SpriteName)
{
	FString Directory = TEXT("/Script/Paper2D.PaperSprite'/Game/09_Image/UI/MinimapIcons/");
	//QuestClear_Sprite.QuestClear_Sprite'
	Directory += SpriteName + TEXT(".") + SpriteName + TEXT("'");
	UPaperSprite* Sprite = LoadObject<UPaperSprite>(NULL, *Directory, NULL, LOAD_None, NULL);
	return Sprite;
}

void ANpc::Interact(AMyPlayer* Player)
{
	auto GInstance = Cast<UMyGameInstance>(GetGameInstance());
	UUserWidget* Widget = GInstance->GetUIMgr()->PopupUI(GetWorld(), UIType::Script);
	auto Script = Cast<UWidget_Script>(Widget);
	if (Script != nullptr)
		Script->SetScript(this);
}

void ANpc::LoadPossibleQuestData(AMyPlayer* Player)
{
	auto GInstance = Cast<UMyGameInstance>(GetGameInstance());
	GInstance->GetQuestMgr()->LoadNpcQuest(this, Player);
	UpdateQuestMark();
}

void ANpc::UpdateQuestMark()
{
	auto NpcWidget = Cast<UWidget_NpcInfo>(NpcInfo->GetUserWidgetObject());
	NpcWidget->UpdateQuestMark();
	SetMinimapIcon();
}

void ANpc::GetIdFromActor()
{
	FString MyName = GetActorNameOrLabel();
	FString BaseName = TEXT("BP_Npc");
	int FullNameLen = MyName.Len();
	int Len = BaseName.Len();
	int Count = FullNameLen = Len;

	FString IdName = MyName.Mid(Len, Count);
	Id = FCString::Atoi(*IdName);
}

void ANpc::SetNpcInfo()
{
	GetIdFromActor();
	auto GInstance = Cast<UMyGameInstance>(GetGameInstance());

	FNpcData* Data = GInstance->GetNpcData(Id);
	Name = Data->Name;
	Job = Data->Job;
	DefaultLine = Data->DefaultLine;

	if (Data->Type == TEXT("Equip"))
		Type = EQUIP_SHOP;
	
	if (Data->Type == TEXT("Use"))
		Type = USE_SHOP;

	if (Data->Type == TEXT("Null"))
		Type = NONE_SHOP;

	auto NpcWidget = Cast<UWidget_NpcInfo>(NpcInfo->GetUserWidgetObject());
	//if (NpcWidget)
	NpcWidget->BindNpc(this);
	UE_LOG(LogTemp, Warning, TEXT("Npc Id Registered! : %d, %s, %s, %d"), Id, *Name, *DefaultLine, (int)Type);

	GInstance->AddNpc(Id, this);

}

void ANpc::SetMinimapIcon()
{
	if (GetQuestComponent()->GetCompletableQuestNum() > 0)
	{
		MinimapIcon->SetSprite(GetSprite(TEXT("QuestClear_Sprite")));
		MinimapIcon->SetRelativeScale3D(FVector(2.f, 2.f, 2.f));

		if(QuestComponent->GetMainCompletableNumber() > 0)
			MinimapIcon->SetSpriteColor(FLinearColor(FColor::Green));
		else
			MinimapIcon->SetSpriteColor(FLinearColor(FColor::Yellow));
	}
	else if (GetQuestComponent()->GetPossibleQuestNum() > 0)
	{
		MinimapIcon->SetSprite(GetSprite(TEXT("QuestPossible_Sprite")));
		MinimapIcon->SetRelativeScale3D(FVector(2.f, 2.f, 2.f));

		if (QuestComponent->GetMainPossibleNumber() > 0)
			MinimapIcon->SetSpriteColor(FLinearColor(FColor::Green));
		else
			MinimapIcon->SetSpriteColor(FLinearColor(FColor::Yellow));
	}
	else if (Type == EQUIP_SHOP)
	{
		MinimapIcon->SetSprite(GetSprite(TEXT("WeaponShop_Sprite")));
		MinimapIcon->SetRelativeScale3D(FVector(0.3f, 0.3f, 0.3f));
		MinimapIcon->SetSpriteColor(FLinearColor(FColor::White));
	}
	else if (Type == USE_SHOP)
	{
		MinimapIcon->SetSprite(GetSprite(TEXT("ItemShop_Sprite")));
		MinimapIcon->SetRelativeScale3D(FVector(1.f, 1.f, 1.f));
		MinimapIcon->SetSpriteColor(FLinearColor(FColor::White));
	}
	else
	{
		MinimapIcon->SetSprite(GetSprite(TEXT("Dot_Sprite")));
		MinimapIcon->SetRelativeScale3D(FVector(0.3f, 0.3f, 0.3f));
	}

}

void ANpc::SetPlayer()
{
	auto Char = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	auto MyPlayer = Cast<AMyPlayer>(Char);
	MainPlayer = MyPlayer;

}

void ANpc::SetVisiblityInfoWidget()
{
	if (GetDistanceTo(Cast<AActor>(MainPlayer)) <= 1500.f)
		NpcInfo->SetVisibility(true);
	else
		NpcInfo->SetVisibility(false);
}

