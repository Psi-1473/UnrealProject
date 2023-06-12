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

AMyPlayerController::AMyPlayerController()
{

	static ConstructorHelpers::FObjectFinder<UInputMappingContext> DEFAULT_CONTEXT(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/03_Input/Player/IMC_Default.IMC_Default'"));
	static ConstructorHelpers::FObjectFinder<UInputAction> IA_MOVE(TEXT("/Script/EnhancedInput.InputAction'/Game/03_Input/Player/Actions/IA_Move.IA_Move'"));
	static ConstructorHelpers::FObjectFinder<UInputAction> IA_LOOK(TEXT("/Script/EnhancedInput.InputAction'/Game/03_Input/Player/Actions/IA_Look.IA_Look'"));
	static ConstructorHelpers::FObjectFinder<UInputAction> IA_JUMP(TEXT("/Script/EnhancedInput.InputAction'/Game/03_Input/Player/Actions/IA_Jump.IA_Jump'"));
	static ConstructorHelpers::FObjectFinder<UInputAction> IA_ATTACK(TEXT("/Script/EnhancedInput.InputAction'/Game/03_Input/Player/Actions/Attack/Sword/IA_SwordAttack.IA_SwordAttack'"));
	static ConstructorHelpers::FObjectFinder<UInputAction> IA_ZOOM(TEXT("/Script/EnhancedInput.InputAction'/Game/03_Input/Player/Actions/IA_ZoomIn.IA_ZoomIn'"));

	if (DEFAULT_CONTEXT.Succeeded())
		DefaultContext = DEFAULT_CONTEXT.Object;

	if (IA_MOVE.Succeeded())MoveAction = IA_MOVE.Object;
	if (IA_LOOK.Succeeded()) LookAction = IA_LOOK.Object;
	if (IA_JUMP.Succeeded()) JumpAction = IA_JUMP.Object;
	if (IA_ATTACK.Succeeded()) Action_AttackSword = IA_ATTACK.Object;
	if (IA_ZOOM.Succeeded()) ZoomAction = IA_ZOOM.Object;
	
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
	}
}

void AMyPlayerController::IA_Zoom(const FInputActionValue& Value)
{
	bZoom = Value.Get<bool>();
	auto Movement = Cast<UCharacterMovementComponent>(MyPlayer->GetMovementComponent());
	Movement->MaxWalkSpeed = (bZoom) ? 350.f : 600.f;
}

void AMyPlayerController::IA_Sword_Attack(const FInputActionValue& Value)
{
	if (Value.Get<bool>())
	{
		if (MyPlayer->GetState() != MyPlayer->GetSpecificState(STATE::ATTACK))
				MyPlayer->SetState(STATE::ATTACK);
		MyPlayer->GetAnimInst()->PlayAttackMontage();

		if (MyPlayer->GetWeapon()->GetType() == WEAPON_ARROW)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = GetInstigator();

			FVector CameraLocation;
			FRotator CameraRotation;
			GetActorEyesViewPoint(CameraLocation, CameraRotation);

			//MyPlayer->GetWeapon()->SetMuzzleOffset(MyPlayer->)
			//FVector MuzzleLocation = FTransform(CameraRotation).TransformVector(MuzzleOffset);
			AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(MyPlayer->GetWeapon()->GetArrow(),
				MyPlayer->GetActorLocation() + FVector(100.f, 0.f, 0.f),
				CameraRotation,
				SpawnParams);
			//if (Projectile)
			//{
			//	//GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, TEXT("Boss : Skill Fire"));
			//	FVector LaunchDirection = GetActorForwardVector();
			//	Projectile->SetIsOwnerPlayer(false);
			//	Projectile->FireInDirection(LaunchDirection);
			//}
		}
	}
		
}
