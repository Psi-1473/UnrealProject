// Fill out your copyright notice in the Description page of Project Settings.


#include "Npc.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "../Player/MyPlayer.h"
#include "../../MyGameInstance.h"
#include "../../Widgets/Popup/Widget_Script.h"
#include "../../ActorComponent/QuestComponent.h"
#include "../../Managers/QuestManager.h"

ANpc::ANpc()
{
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	InteractBox = CreateDefaultSubobject<UBoxComponent>(TEXT("InteractBox"));
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	QuestComponent = CreateDefaultSubobject<UQuestComponent>(TEXT("QuestComponent"));

	Mesh->SetRelativeLocation(FVector(0.f, 0.f, -88.f));
	Mesh->SetRelativeRotation(FRotator(0.f, -90.f, -0.f));

	InteractBox->SetRelativeScale3D(FVector(3.f, 3.f, 3.f));
	InteractBox->SetCollisionProfileName("InteractBox");

	CapsuleComponent->SetCapsuleHalfHeight(88.f);
	CapsuleComponent->SetCapsuleRadius(34.f);

	RootComponent = CapsuleComponent;
	InteractBox->SetupAttachment(RootComponent);
	Mesh->SetupAttachment(RootComponent);
	// 박스 사이즈 조절

	InteractBox->OnComponentBeginOverlap.AddDynamic(this, &IInteractable::OnOverlapBegin);
	InteractBox->OnComponentEndOverlap.AddDynamic(this, &IInteractable::OnOverlapEnd);
}

void ANpc::BeginPlay()
{
	AActor::BeginPlay();
	SetNpcInfo();
	LoadPossibleQuestData();
}

void ANpc::Interact(AMyPlayer* Player)
{
	auto GInstance = Cast<UMyGameInstance>(GetGameInstance());
	UUserWidget* Widget = GInstance->GetUIMgr()->PopupUI(GetWorld(), UIType::Script);
	auto Script = Cast<UWidget_Script>(Widget);
	if (Script != nullptr)
		Script->SetScript(this);
}

void ANpc::LoadPossibleQuestData()
{
	auto GInstance = Cast<UMyGameInstance>(GetGameInstance());
	GInstance->GetQuestMgr()->LoadNpcQuest(this);
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
	DefaultLine = Data->DefaultLine;

	if (Data->Type == TEXT("Equip"))
		Type = EQUIP_SHOP;
	
	if (Data->Type == TEXT("Use"))
		Type = USE_SHOP;

	if (Data->Type == TEXT("Null"))
		Type = NONE_SHOP;

	UE_LOG(LogTemp, Warning, TEXT("Npc Id Registered! : %d, %s, %s, %d"), Id, *Name, *DefaultLine, (int)Type);
}

