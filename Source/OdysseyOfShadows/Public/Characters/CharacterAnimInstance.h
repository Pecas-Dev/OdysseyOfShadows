#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CharacterAnimInstance.generated.h"

/**
 *
 */
UCLASS()
class ODYSSEYOFSHADOWS_API UCharacterAnimInstance : public UAnimInstance
{


	GENERATED_BODY()


public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaTime) override;

	UPROPERTY(BlueprintReadOnly)
		class AOdysseyOfShadowsCharacter* odysseyOfShadowsCharacter;

	UPROPERTY(BlueprintReadOnly, Category = Movement)
		class UCharacterMovementComponent* odysseyOfShadowsCharacterMovement;

	UPROPERTY(BlueprintReadOnly, Category = Movement)
		float groundSpeed;

	UPROPERTY(BlueprintReadOnly, Category = Movement)
		bool isFalling;

protected:


private:

};
