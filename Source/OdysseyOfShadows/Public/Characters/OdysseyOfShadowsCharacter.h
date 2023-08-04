#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "OdysseyOfShadowsCharacter.generated.h"

UCLASS()
class ODYSSEYOFSHADOWS_API AOdysseyOfShadowsCharacter : public ACharacter
{

	GENERATED_BODY()

public:
	AOdysseyOfShadowsCharacter();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void Jump() override;

protected:

	virtual void BeginPlay() override;

	void Move(const FInputActionValue& value);
	void Look(const FInputActionValue& value);
	void Attack();
	void Equip();
	void Dodge();


	FRotator characterCameraRotation = FRotator(0.f, -20.f, 0.f);


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
		class UInputMappingContext* characterMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
		class UInputAction* characterMoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
		class UInputAction* lookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
		class UInputAction* jumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
		class UInputAction* equipAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
		class UInputAction* attackAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
		class UInputAction* dodgeAction;

private:

	UPROPERTY(VisibleAnywhere)
		class USpringArmComponent* cameraBoom;

	UPROPERTY(VisibleAnywhere)
		class UCameraComponent* viewCamera;

	UPROPERTY(VisibleAnywhere, Category = Hair)
		class UGroomComponent* characterHair;

	UPROPERTY(VisibleAnywhere, Category = Hair)
		class UGroomComponent* characterEyebrows;
};
