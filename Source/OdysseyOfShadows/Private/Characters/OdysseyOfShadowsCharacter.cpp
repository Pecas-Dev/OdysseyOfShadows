#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GroomComponent.h"
#include "Items/Item.h"
#include "Items/Weapons/Weapon.h"
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
	Super::Jump();
}

void AOdysseyOfShadowsCharacter::Equip()
{
	AWeapon* overlappingWeapon = Cast<AWeapon>(overlappingItem);

	if (overlappingWeapon)
	{
		overlappingWeapon->Equip(GetMesh(), FName("RightHandSocket"));
	}
}

void AOdysseyOfShadowsCharacter::Attack()
{
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
		/*enhancedInputComponent->BindAction(attackAction, ETriggerEvent::Triggered, this, &AOdysseyOfShadowsCharacter::Attack);
		enhancedInputComponent->BindAction(dodgeAction, ETriggerEvent::Triggered, this, &AOdysseyOfShadowsCharacter::Dodge);*/
	}
}



