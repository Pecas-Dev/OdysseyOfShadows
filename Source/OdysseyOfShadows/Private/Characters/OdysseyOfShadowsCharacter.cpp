#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GroomComponent.h"
#include "Items/Item.h"
#include "Items/Weapons/Weapon.h"
#include "Animation/AnimMontage.h"
#include "Characters/OdysseyOfShadowsCharacter.h"

AOdysseyOfShadowsCharacter::AOdysseyOfShadowsCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;

	cameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	cameraBoom->SetupAttachment(GetRootComponent());
	cameraBoom->TargetArmLength = 300.f;

	viewCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("ViewCamera"));
	viewCamera->SetupAttachment(cameraBoom);

	characterHair = CreateDefaultSubobject<UGroomComponent>(TEXT("Hair"));
	characterHair->SetupAttachment(GetMesh());
	characterHair->AttachmentName = FString("head");

	characterEyebrows = CreateDefaultSubobject<UGroomComponent>(TEXT("Eyebrows"));
	characterEyebrows->SetupAttachment(GetMesh());
	characterEyebrows->AttachmentName = FString("head");
}

void AOdysseyOfShadowsCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* playerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(playerController->GetLocalPlayer()))
		{
			subsystem->AddMappingContext(characterMappingContext, 0);
		}
	}
}


void AOdysseyOfShadowsCharacter::Move(const FInputActionValue& value)
{
	if (actionState != EActionState::EAS_Unoccupied ) { return; }


	const FVector2D movementVector = value.Get<FVector2D>();
	const FRotator rotation = Controller->GetControlRotation();
	const FRotator yawRotation(0.f, rotation.Yaw, 0.f);
	const FVector forwardRotation = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::X);
	const FVector rightDirection = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::Y);

	AddMovementInput(forwardRotation, movementVector.Y);
	AddMovementInput(rightDirection, movementVector.X);
}

void AOdysseyOfShadowsCharacter::Look(const FInputActionValue& value)
{
	const FVector2D lookAxisVector = value.Get<FVector2D>();

	AddControllerYawInput(lookAxisVector.X);
	AddControllerPitchInput(lookAxisVector.Y);
}


void AOdysseyOfShadowsCharacter::Jump()
{
	if (actionState != EActionState::EAS_Unoccupied) { return; }


	if (GetWorld()->TimeSeconds - lastJumpTime >= 1.25f)
	{
		Super::Jump();

		lastJumpTime = GetWorld()->TimeSeconds;
	}
}

void AOdysseyOfShadowsCharacter::StopJumping()
{
	Super::StopJumping();
}

void AOdysseyOfShadowsCharacter::Equip()
{
	AWeapon* overlappingWeapon = Cast<AWeapon>(overlappingItem);

	if (overlappingWeapon)
	{
		overlappingWeapon->Equip(GetMesh(), FName("RightHandSocket"));
		characterState = ECharacterState::ECS_EquippedOneHandedWeapon;
		overlappingItem = nullptr;
		equippedWeapon = overlappingWeapon;
	}
	else
	{
		if (CanDisarm())
		{
			PlayEquipMontage(FName("Unequip"));
			characterState = ECharacterState::ECS_Unequipped;
			actionState = EActionState::EAS_EquippingWeapon;
		}
		else if (CanArm())
		{
			PlayEquipMontage(FName("Equip"));
			characterState = ECharacterState::ECS_EquippedOneHandedWeapon;
			actionState = EActionState::EAS_EquippingWeapon;
		}
	}


}

void AOdysseyOfShadowsCharacter::Attack()
{
	if (CanAttack())
	{
		PlayAttackMontage();
		actionState = EActionState::EAS_Attacking;
	}
}

bool AOdysseyOfShadowsCharacter::CanAttack()
{
	return actionState == EActionState::EAS_Unoccupied && characterState != ECharacterState::ECS_Unequipped;
}

bool AOdysseyOfShadowsCharacter::CanDisarm()
{
	return actionState == EActionState::EAS_Unoccupied && characterState != ECharacterState::ECS_Unequipped;
}

bool AOdysseyOfShadowsCharacter::CanArm()
{
	return actionState == EActionState::EAS_Unoccupied && characterState == ECharacterState::ECS_Unequipped && equippedWeapon;
}

void AOdysseyOfShadowsCharacter::PlayAttackMontage()
{
	UAnimInstance* animInstance = GetMesh()->GetAnimInstance();

	if (animInstance && attackMontage)
	{
		animInstance->Montage_Play(attackMontage);
		const int32 selectionRandom = FMath::RandRange(0, 2);

		FName sectionName = FName();

		switch (selectionRandom)
		{
		case 0:
			sectionName = FName("Attack1");
			break;

		case 1:
			sectionName = FName("Attack2");
			break;

		case 2:
			sectionName = FName("Attack3");
			break;

		default:
			break;
		}

		animInstance->Montage_JumpToSection(sectionName, attackMontage);
	}
}

void AOdysseyOfShadowsCharacter::PlayEquipMontage(FName sectionName)
{
	UAnimInstance* animInstanceEquip = GetMesh()->GetAnimInstance();

	if (animInstanceEquip && equipkMontage)
	{
		animInstanceEquip->Montage_Play(equipkMontage);

		animInstanceEquip->Montage_JumpToSection(sectionName, equipkMontage);
	}
}



void AOdysseyOfShadowsCharacter::AttackEnd()
{
	actionState = EActionState::EAS_Unoccupied;
}

void AOdysseyOfShadowsCharacter::Disarm()
{
	if (equippedWeapon)
	{
		equippedWeapon->AttachMeshToSocket(GetMesh(), FName("SpineSocket"));
	}
}

void AOdysseyOfShadowsCharacter::Arm()
{
	if (equippedWeapon)
	{
		equippedWeapon->AttachMeshToSocket(GetMesh(), FName("RightHandSocket"));
	}
}

void AOdysseyOfShadowsCharacter::FinishEquipping()
{
	actionState = EActionState::EAS_Unoccupied;
}

void AOdysseyOfShadowsCharacter::Dodge()
{
}


void AOdysseyOfShadowsCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AOdysseyOfShadowsCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* enhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		enhancedInputComponent->BindAction(characterMoveAction, ETriggerEvent::Triggered, this, &AOdysseyOfShadowsCharacter::Move);
		enhancedInputComponent->BindAction(lookAction, ETriggerEvent::Triggered, this, &AOdysseyOfShadowsCharacter::Look);
		enhancedInputComponent->BindAction(jumpAction, ETriggerEvent::Triggered, this, &AOdysseyOfShadowsCharacter::Jump);
		enhancedInputComponent->BindAction(equipAction, ETriggerEvent::Triggered, this, &AOdysseyOfShadowsCharacter::Equip);
		enhancedInputComponent->BindAction(attackAction, ETriggerEvent::Triggered, this, &AOdysseyOfShadowsCharacter::Attack);
		/*enhancedInputComponent->BindAction(dodgeAction, ETriggerEvent::Triggered, this, &AOdysseyOfShadowsCharacter::Dodge);*/
	}
}



