#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "InputActionValue.h"
#include "Bird.generated.h"

UCLASS()
class ODYSSEYOFSHADOWS_API ABird : public APawn
{
	GENERATED_BODY()

public:
	ABird();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;

	void MoveForward(const FInputActionValue& value);
	void Look(const FInputActionValue& value);


	FRotator cameraRotation = FRotator(0.f, -30.f, 0.f);


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
		class UInputMappingContext* birdMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
		class UInputAction* moveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
		class UInputAction* lookAction;

private:
	UPROPERTY(VisibleAnywhere)
		class UCapsuleComponent* capsule;

	UPROPERTY(VisibleAnywhere)
		class USkeletalMeshComponent* birdMesh;

	UPROPERTY(VisibleAnywhere)
		class USpringArmComponent* cameraBoom;

	UPROPERTY(VisibleAnywhere)
		class UCameraComponent* viewCamera;
};
