#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Components/InputComponent.h"
#include "Characters/OdysseyOfShadowsCharacter.h"

AOdysseyOfShadowsCharacter::AOdysseyOfShadowsCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
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

}

void AOdysseyOfShadowsCharacter::Equip()
{

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
		/*enhancedInputComponent->BindAction(equipAction, ETriggerEvent::Triggered, this, &AOdysseyOfShadowsCharacter::Equip);
		enhancedInputComponent->BindAction(attackAction, ETriggerEvent::Triggered, this, &AOdysseyOfShadowsCharacter::Attack);
		enhancedInputComponent->BindAction(dodgeAction, ETriggerEvent::Triggered, this, &AOdysseyOfShadowsCharacter::Dodge);*/
	}
}



