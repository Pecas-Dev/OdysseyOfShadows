#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "CharacterTypes.h"
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
	virtual void StopJumping() override;

	UFUNCTION(BlueprintCallable)
	void SetWeaponCollisionEnabled(ECollisionEnabled::Type collisionEnabled);

	/*UFUNCTION(BlueprintCallable)
	void SetWeaponCollisionDisabled(ECollisionEnabled::Type collisionDisabled);*/


protected:

	virtual void BeginPlay() override;

	void Move(const FInputActionValue& value);
	void Look(const FInputActionValue& value);
	void Attack();
	void Equip();
	void Dodge();

	void PlayAttackMontage();
	void PlayEquipMontage(const FName& sectionName);


	bool CanAttack();
	bool CanDisarm();
	bool CanArm();


	UFUNCTION(BlueprintCallable)
	void AttackEnd();

	UFUNCTION(BlueprintCallable)
	void Disarm();

	UFUNCTION(BlueprintCallable)
	void Arm();

	UFUNCTION(BlueprintCallable)
	void FinishEquipping();



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



	FRotator characterCameraRotation = FRotator(0.f, -20.f, 0.f);

private:

	UPROPERTY(VisibleAnywhere)
	class USpringArmComponent* cameraBoom;

	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* viewCamera;

	//UPROPERTY(VisibleAnywhere, Category = Hair)
	//class UGroomComponent* characterHair;

	//UPROPERTY(VisibleAnywhere, Category = Hair)
	//class UGroomComponent* characterEyebrows;

	UPROPERTY(VisibleInstanceOnly)
	class AItem* overlappingItem;

	UPROPERTY(EditDefaultsOnly, Category = Montages)
	class UAnimMontage* attackMontage;

	UPROPERTY(EditDefaultsOnly, Category = Montages)
	class UAnimMontage* equipkMontage;

	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	EActionState actionState = EActionState::EAS_Unoccupied;

	UPROPERTY(VisibleAnywhere, Category = Weapon)
	class AWeapon* equippedWeapon;


	ECharacterState characterState = ECharacterState::ECS_Unequipped;

	//bool bCanJump = true;
	float lastJumpTime = 0.f;

public:
	FORCEINLINE void SetOverlappingItem(AItem* item) { overlappingItem = item; }
	FORCEINLINE ECharacterState GetCharacterState() const { return characterState; }
};

