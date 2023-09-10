// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "MyPlayer.h"
#include "../../Items/Weapons/Weapon.h"
#include "../../State/CharacterState.h"
#include "../../Animations/Player/PlayerAnim.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "../../Projectiles/Projectile.h"
#include "../../Projectiles/Player/Arrow.h"
#include "Camera/CameraComponent.h"
#include "../../Skills/Components/PlayerSkillComponent.h"
#include "../../Skills/EffectActor/SkillRangeActor.h"
#include "../../Skills/Skill.h"
#include "../../Skills/Player/PlayerSkill.h"
#include "../../MyGameInstance.h"
#include "../../Managers/UIManager.h"
#include "../../MyGameMode.h"
#include "../../Widgets/Widget_PlayerMain.h"


AMyPlayerController::AMyPlayerController()
{

	static ConstructorHelpers::FObjectFinder<UInputMappingContext> DEFAULT_CONTEXT(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/03_Input/Player/IMC_Default.IMC_Default'"));
	static ConstructorHelpers::FObjectFinder<UInputAction> IA_MOVE(TEXT("/Script/EnhancedInput.InputAction'/Game/03_Input/Player/Actions/IA_Move.IA_Move'"));
	static ConstructorHelpers::FObjectFinder<UInputAction> IA_LOOK(TEXT("/Script/EnhancedInput.InputAction'/Game/03_Input/Player/Actions/IA_Look.IA_Look'"));
	static ConstructorHelpers::FObjectFinder<UInputAction> IA_JUMP(TEXT("/Script/EnhancedInput.InputAction'/Game/03_Input/Player/Actions/IA_Jump.IA_Jump'"));
	static ConstructorHelpers::FObjectFinder<UInputAction> IA_ATTACK(TEXT("/Script/EnhancedInput.InputAction'/Game/03_Input/Player/Actions/Attack/Sword/IA_SwordAttack.IA_SwordAttack'"));
	static ConstructorHelpers::FObjectFinder<UInputAction> IA_ZOOM(TEXT("/Script/EnhancedInput.InputAction'/Game/03_Input/Player/Actions/IA_ZoomIn.IA_ZoomIn'"));
	static ConstructorHelpers::FObjectFinder<UInputAction> IA_Q(TEXT("/Script/EnhancedInput.InputAction'/Game/03_Input/Player/Actions/Skill/IA_SkillQ.IA_SkillQ'"));
	static ConstructorHelpers::FObjectFinder<UInputAction> IA_E(TEXT("/Script/EnhancedInput.InputAction'/Game/03_Input/Player/Actions/Skill/IA_SkillE.IA_SkillE'"));
	static ConstructorHelpers::FObjectFinder<UInputAction> IA_R(TEXT("/Script/EnhancedInput.InputAction'/Game/03_Input/Player/Actions/Skill/IA_SkillR.IA_SkillR'"));
	static ConstructorHelpers::FObjectFinder<UInputAction> IA_Inven(TEXT("/Script/EnhancedInput.InputAction'/Game/03_Input/Player/Actions/UI/IA_Inventory.IA_Inventory'"));
	static ConstructorHelpers::FObjectFinder<UInputAction> IA_Interact(TEXT("/Script/EnhancedInput.InputAction'/Game/03_Input/Player/Actions/IA_Interact.IA_Interact'"));
	static ConstructorHelpers::FObjectFinder<UInputAction> IA_Skill(TEXT("/Script/EnhancedInput.InputAction'/Game/03_Input/Player/Actions/UI/IA_Skill.IA_Skill'"));
	static ConstructorHelpers::FObjectFinder<UInputAction> IA_Quick1(TEXT("/Script/EnhancedInput.InputAction'/Game/03_Input/Player/Actions/IA_Quick1.IA_Quick1'"));
	static ConstructorHelpers::FObjectFinder<UInputAction> IA_Quick2(TEXT("/Script/EnhancedInput.InputAction'/Game/03_Input/Player/Actions/IA_Quick2.IA_Quick2'"));
	static ConstructorHelpers::FObjectFinder<UInputAction> IA_Quick3(TEXT("/Script/EnhancedInput.InputAction'/Game/03_Input/Player/Actions/IA_Quick3.IA_Quick3'"));


	if (DEFAULT_CONTEXT.Succeeded())
		DefaultContext = DEFAULT_CONTEXT.Object;

	if (IA_MOVE.Succeeded())MoveAction = IA_MOVE.Object;
	if (IA_LOOK.Succeeded()) LookAction = IA_LOOK.Object;
	if (IA_JUMP.Succeeded()) JumpAction = IA_JUMP.Object;
	if (IA_ATTACK.Succeeded()) Action_AttackSword = IA_ATTACK.Object;
	if (IA_ZOOM.Succeeded()) ZoomAction = IA_ZOOM.Object;
	if (IA_Q.Succeeded()) Push_Q = IA_Q.Object;
	if (IA_E.Succeeded()) Push_E = IA_E.Object;
	if (IA_R.Succeeded()) Push_R = IA_R.Object;
	if (IA_Inven.Succeeded()) InvenAction = IA_Inven.Object;
	if (IA_Interact.Succeeded()) InteractAction = IA_Interact.Object;
	if (IA_Skill.Succeeded()) SkillUIAction = IA_Skill.Object;
	if (IA_Quick1.Succeeded()) Quick1 = IA_Quick1.Object;
	if (IA_Quick2.Succeeded()) Quick2 = IA_Quick2.Object;
	if (IA_Quick3.Succeeded()) Quick3 = IA_Quick3.Object;
	
}

void AMyPlayerController::BeginPlay()
{
	MyPlayer = Cast<AMyPlayer>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (UEnhancedInputLocalPlayerSubsystem* SubSystem = 
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
			SubSystem->AddMappingContext(DefaultContext, 0);
}

void AMyPlayerController::SetupInputComponent()
{
	APlayerController::SetupInputComponent();

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMyPlayerController::IA_Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMyPlayerController::IA_Look);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &AMyPlayerController::IA_Jump);
		EnhancedInputComponent->BindAction(Action_AttackSword, ETriggerEvent::Triggered, this, &AMyPlayerController::IA_Sword_Attack);
		EnhancedInputComponent->BindAction(ZoomAction, ETriggerEvent::Triggered, this, &AMyPlayerController::IA_Zoom);
		EnhancedInputComponent->BindAction(Push_Q, ETriggerEvent::Triggered, this, &AMyPlayerController::IA_Push_Q);
		EnhancedInputComponent->BindAction(Push_E, ETriggerEvent::Triggered, this, &AMyPlayerController::IA_Push_E);
		EnhancedInputComponent->BindAction(Push_R, ETriggerEvent::Triggered, this, &AMyPlayerController::IA_Push_R);
		EnhancedInputComponent->BindAction(InvenAction, ETriggerEvent::Triggered, this, &AMyPlayerController::IA_Inventory);
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Triggered, this, &AMyPlayerController::IA_Interact);
		EnhancedInputComponent->BindAction(SkillUIAction, ETriggerEvent::Triggered, this, &AMyPlayerController::IA_Skill);
		EnhancedInputComponent->BindAction(Quick1, ETriggerEvent::Triggered, this, &AMyPlayerController::IA_Quick1);
		EnhancedInputComponent->BindAction(Quick2, ETriggerEvent::Triggered, this, &AMyPlayerController::IA_Quick2);
		EnhancedInputComponent->BindAction(Quick3, ETriggerEvent::Triggered, this, &AMyPlayerController::IA_Quick3);
	}

}

void AMyPlayerController::Fire()
{
	FVector ArrowDir = GetViewportToWorld();
	FireArrow(ArrowDir);
}

void AMyPlayerController::FireArrow(FVector DestPos)
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = MyPlayer;
	SpawnParams.Instigator = MyPlayer->GetInstigator();

	FVector CameraLocation;
	FRotator CameraRotation;
	MyPlayer->GetActorEyesViewPoint(CameraLocation, CameraRotation);
	CameraRotation.Pitch += 5.f;
	AProjectile* Projectile = GetWorld()->SpawnActor<AArrow>(MyPlayer->GetWeapon()->GetArrow(),
		MyPlayer->GetActorLocation() + MyPlayer->GetActorRightVector() * 15.f + MyPlayer->GetActorUpVector() * 65.f,
		CameraRotation,
		SpawnParams);
	FVector ArrowVector;
	if (bArrowTarget)
		ArrowVector = DestPos - Projectile->GetActorLocation();
	else
		ArrowVector = DestPos;
	ArrowVector.Normalize();
	if (Projectile)
	{
		if (bZoom)
			Projectile->SetAttackStrength(true);
		else
			Projectile->SetAttackStrength(false);
		Projectile->FireInDirection(ArrowVector, 2.f);
	}
}

void AMyPlayerController::IA_Move(const FInputActionValue& Value)
{
	if (MyPlayer == nullptr)
		return;

	if (MyPlayer->GetState() != MyPlayer->GetSpecificState(STATE::IDLE) &&
		MyPlayer->GetState() != MyPlayer->GetSpecificState(STATE::MOVE) &&
		MyPlayer->GetState() != MyPlayer->GetSpecificState(STATE::JUMP))
		return;

	if (MyPlayer->GetState() != MyPlayer->GetSpecificState(STATE::MOVE) &&
		MyPlayer->GetState() != MyPlayer->GetSpecificState(STATE::JUMP))
		MyPlayer->SetState(STATE::MOVE);

	const FVector2D MovementVector = Value.Get<FVector2D>();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

	Horizontal = MovementVector.X;
	Vertical = MovementVector.Y;

	MyPlayer->AddMovementInput(ForwardDirection, MovementVector.Y);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	MyPlayer->AddMovementInput(RightDirection, MovementVector.X);
}

void AMyPlayerController::IA_Look(const FInputActionValue& Value)
{
	if (MyPlayer == nullptr)
		return;
	FVector2D LookVector = Value.Get<FVector2D>();

	if (MyPlayer->GetSpawnedRangeActor() != nullptr)
	{
		FVector RightDir = MyPlayer->GetActorRightVector() * LookVector.X * 50;
		FVector ForwardDir = MyPlayer->GetActorForwardVector() * LookVector.Y * 50;
		FVector MoveDir = RightDir + ForwardDir;

		MyPlayer->GetSpawnedRangeActor()->MoveRangeActor(MoveDir, MyPlayer->GetActorLocation(), 1000.f);
		return;
	}

	if (LookVector.X > 1.f) LookVector.X = 1.f;
	else if (LookVector.X < -1.f) LookVector.X = -1.f;

	if (LookVector.Y > 1.f) LookVector.Y = 1.f;
	else if (LookVector.Y < -1.f) LookVector.Y = -1.f;

	MyPlayer->AddControllerYawInput(LookVector.X * MouseSpeed);
	MyPlayer->AddControllerPitchInput(-1 * LookVector.Y * MouseSpeed);
	
	
}

void AMyPlayerController::IA_Jump(const FInputActionValue& Value)
{
	if (Value.Get<bool>())
	{
		if (MyPlayer->GetState() != MyPlayer->GetSpecificState(STATE::IDLE) &&
			MyPlayer->GetState() != MyPlayer->GetSpecificState(STATE::MOVE))
			return;
		MyPlayer->Jump();
		MyPlayer->SetState(STATE::JUMP);
	}
}

void AMyPlayerController::IA_Zoom(const FInputActionValue& Value)
{
	if (MyPlayer->GetInstance()->GetUIMgr()->GetUiNumber() > 0)
		return;

	if (MyPlayer->GetWeapon()->GetType() != WEAPONTYPE::WEAPON_ARROW)
	{
		FString Str = FString::FromInt((int)MyPlayer->GetWeapon()->GetType());
		UE_LOG(LogTemp, Warning, TEXT("WEAPON IS NOT A BOW : %s"), *Str);
		return;
	}
	if (MyPlayer->GetState() == MyPlayer->GetSpecificState(STATE::ATTACK) && CameraMoved == false)
		return;
	bZoom = Value.Get<bool>();
	if (bZoom)
		ZoomIn();
	else
		ZoomOut();
}

void AMyPlayerController::IA_Push_Q(const FInputActionValue& Value)
{
	if (!Value.Get<bool>())
		return;

	if (MyPlayer->GetState() == MyPlayer->GetSpecificState(STATE::SKILL))
		return;

	if (MyPlayer->GetState() == MyPlayer->GetSpecificState(STATE::SKILLCAST))
		MyPlayer->GetSkillComponent()->CancleCast(KEY_Q);
	else
		MyPlayer->GetSkillComponent()->ExecuteSkill(KEY_Q);
}

void AMyPlayerController::IA_Push_E(const FInputActionValue& Value)
{
	if (!Value.Get<bool>())
		return;

	if (MyPlayer->GetState() == MyPlayer->GetSpecificState(STATE::SKILL))
		return;

	if (MyPlayer->GetState() == MyPlayer->GetSpecificState(STATE::SKILLCAST))
		MyPlayer->GetSkillComponent()->CancleCast(KEY_E);
	else
		MyPlayer->GetSkillComponent()->ExecuteSkill(KEY_E);
}

void AMyPlayerController::IA_Push_R(const FInputActionValue& Value)
{
	if (!Value.Get<bool>())
		return;
	if (MyPlayer->GetState() == MyPlayer->GetSpecificState(STATE::SKILL))
		return;

	if (MyPlayer->GetState() == MyPlayer->GetSpecificState(STATE::SKILLCAST))
		MyPlayer->GetSkillComponent()->CancleCast(KEY_R);
	else
		MyPlayer->GetSkillComponent()->ExecuteSkill(KEY_R);
}

void AMyPlayerController::IA_Inventory(const FInputActionValue& Value)
{
	auto GInstance = Cast<UMyGameInstance>(GetGameInstance());
	GInstance->GetUIMgr()->PopupUI(GetWorld(), UIType::Inventory);
}

void AMyPlayerController::IA_Interact(const FInputActionValue& Value)
{
	MyPlayer->Interact();
}

void AMyPlayerController::IA_Skill(const FInputActionValue& Value)
{
	auto GInstance = Cast<UMyGameInstance>(GetGameInstance());
	GInstance->GetUIMgr()->PopupUI(GetWorld(), UIType::Skill);
}

void AMyPlayerController::IA_Quick1(const FInputActionValue& Value)
{
	if (Value.Get<bool>())
	{
		auto MyGameMode = Cast<AMyGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
		if (MyGameMode == nullptr) return;

		auto MainWidget = Cast<UWidget_PlayerMain>(MyGameMode->GetCurrentWidget());
		if (MainWidget == nullptr) return;

		MainWidget->PressQuickSlot(0);
	}
}

void AMyPlayerController::IA_Quick2(const FInputActionValue& Value)
{
	if (Value.Get<bool>())
	{
		auto MyGameMode = Cast<AMyGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
		if (MyGameMode == nullptr) return;

		auto MainWidget = Cast<UWidget_PlayerMain>(MyGameMode->GetCurrentWidget());
		if (MainWidget == nullptr) return;

		MainWidget->PressQuickSlot(1);
	}
}

void AMyPlayerController::IA_Quick3(const FInputActionValue& Value)
{
	if (Value.Get<bool>())
	{
		auto MyGameMode = Cast<AMyGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
		if (MyGameMode == nullptr) return;

		auto MainWidget = Cast<UWidget_PlayerMain>(MyGameMode->GetCurrentWidget());
		if (MainWidget == nullptr) return;

		MainWidget->PressQuickSlot(2);
	}
}

void AMyPlayerController::IA_Sword_Attack(const FInputActionValue& Value)
{
	if (MyPlayer->GetInstance()->GetUIMgr()->GetUiNumber() > 0)
		return;

	if (MyPlayer->GetState() != MyPlayer->GetSpecificState(STATE::IDLE) &&
		MyPlayer->GetState() != MyPlayer->GetSpecificState(STATE::MOVE) &&
		MyPlayer->GetState() != MyPlayer->GetSpecificState(STATE::JUMP) &&
		MyPlayer->GetState() != MyPlayer->GetSpecificState(STATE::ATTACK) &&
		MyPlayer->GetState() != MyPlayer->GetSpecificState(STATE::SKILLCAST))
		return;

	if (Value.Get<bool>())
	{
		if (MyPlayer->GetState() == MyPlayer->GetSpecificState(STATE::SKILL))
			return;

		if (MyPlayer->GetState() == MyPlayer->GetSpecificState(STATE::SKILLCAST))
			MyPlayer->GetSkill()->CastToExecute(MyPlayer);
		else
		{
			if (MyPlayer->GetState() != MyPlayer->GetSpecificState(STATE::ATTACK))
				MyPlayer->SetState(STATE::ATTACK);
		
			MyPlayer->GetAnimInst()->PlayAttackMontage();
		}
	}
		
}

FVector AMyPlayerController::GetViewportToWorld()
{
	int ViewportX, ViewportY;
	FVector WorldPos;
	FVector WorldDir;

	GetViewportSize(ViewportX, ViewportY);
	ViewportX = ViewportX / 2;
	ViewportY = ViewportY / 2;
	ViewportY -= 10;
	DeprojectScreenPositionToWorld((float)ViewportX, (float)ViewportY, WorldPos, WorldDir);
	UE_LOG(LogTemp, Warning, TEXT("%f, %f, %f"), WorldPos.X, WorldPos.Y, WorldPos.Z);
	UE_LOG(LogTemp, Warning, TEXT("%f, %f, %f"), WorldDir.X, WorldDir.Y, WorldDir.Z);

	FVector ResultDir = GetArrowDir(WorldPos, WorldDir);
	return ResultDir;
}

FVector AMyPlayerController::GetArrowDir(FVector Start, FVector Dir)
{
	FVector EndPos = Start + (Dir * 5000.f);
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes; // 히트 가능한 오브젝트 유형들.
	TEnumAsByte<EObjectTypeQuery> WorldStatic = UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldStatic);
	TEnumAsByte<EObjectTypeQuery> WorldDynamic = UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldDynamic);
	TEnumAsByte<EObjectTypeQuery> MonsterCol = UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_GameTraceChannel2);
	TEnumAsByte<EObjectTypeQuery> PawnCol = UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn);
	ObjectTypes.Add(WorldStatic);
	ObjectTypes.Add(WorldDynamic);
	ObjectTypes.Add(MonsterCol);
	ObjectTypes.Add(PawnCol);

	TArray<AActor*> IgnoreActors; // 무시할 액터들.

	FHitResult HitResult; // 히트 결과 값 받을 변수.

	bool Result = UKismetSystemLibrary::LineTraceSingleForObjects(
		GetWorld(),
		Start,
		EndPos,
		ObjectTypes,
		false,
		IgnoreActors, // 무시할 것이 없다고해도 null을 넣을 수 없다.
		EDrawDebugTrace::ForDuration,
		HitResult,
		true
		// 여기 밑에 3개는 기본 값으로 제공됨. 바꾸려면 적으면 됨.
		//, FLinearColor::Red
		//, FLinearColor::Green
		//, 5.0f
	);
	FVector DestinationPos;
	if (Result == true)
	{
		DestinationPos = HitResult.Location;
		bArrowTarget = true;
		UE_LOG(LogTemp, Warning, TEXT("Arrow Hit O"));
	}
	else
	{
		DestinationPos = Dir;
		bArrowTarget = false;
		UE_LOG(LogTemp, Warning, TEXT("Arrow Hit X"));
	}
	return DestinationPos;
}

void AMyPlayerController::ZoomIn()
{
	if (MyPlayer->GetState() != MyPlayer->GetSpecificState(STATE::IDLE) &&
		MyPlayer->GetState() != MyPlayer->GetSpecificState(STATE::MOVE) &&
		MyPlayer->GetState() != MyPlayer->GetSpecificState(STATE::JUMP))
		return;
	auto Movement = Cast<UCharacterMovementComponent>(MyPlayer->GetMovementComponent());
	MyPlayer->GetCamera()->SetRelativeLocation(MyPlayer->GetCamera()->GetRelativeLocation() + FVector(0.f, 60.f, 0.f));
	MyPlayer->GetCamera()->FieldOfView = 75.f;
	Movement->MaxWalkSpeed = 350.f;
	CameraMoved = true;
}

void AMyPlayerController::ZoomOut()
{
	if (CameraMoved == false) return;
	auto Movement = Cast<UCharacterMovementComponent>(MyPlayer->GetMovementComponent());
	MyPlayer->GetCamera()->SetRelativeLocation(MyPlayer->GetCamera()->GetRelativeLocation() + FVector(0.f, -60.f, 0.f));
	MyPlayer->GetCamera()->FieldOfView = 90.f;
	Movement->MaxWalkSpeed = 600.f;
	CameraMoved = false;
}
