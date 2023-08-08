#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Characters/OdysseyOfShadowsCharacter.h"
#include "Characters/CharacterAnimInstance.h"

void UCharacterAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	odysseyOfShadowsCharacter = Cast<AOdysseyOfShadowsCharacter>(TryGetPawnOwner());

	if (odysseyOfShadowsCharacter)
	{
		odysseyOfShadowsCharacterMovement = odysseyOfShadowsCharacter->GetCharacterMovement();
	}
}

void UCharacterAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);

	if (odysseyOfShadowsCharacterMovement)
	{
		groundSpeed = UKismetMathLibrary::VSizeXY(odysseyOfShadowsCharacterMovement->Velocity);

		isFalling = odysseyOfShadowsCharacterMovement->IsFalling();
	}
}
