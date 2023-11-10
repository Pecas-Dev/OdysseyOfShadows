#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/HitInterface.h"
#include "Enemy.generated.h"

UCLASS()
class ODYSSEYOFSHADOWS_API AEnemy : public ACharacter, public IHitInterface
{

	GENERATED_BODY()

public:
	AEnemy();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void GetHit(const FVector& impactPoint) override;

	void DirectionalHitReact(const FVector& impactPoint);


protected:
	virtual void BeginPlay() override;

	void PlayHitReactMontage(const FName& sectionName);

private:

	UPROPERTY(EditDefaultsOnly, Category = Montages)
	class UAnimMontage* hitReactMontage;

	UPROPERTY(EditAnywhere, Category = Sounds)
	class USoundBase* hitSound;

	UPROPERTY(EditAnywhere, Category = VisualEffects)
	class UParticleSystem* hitParticles; 
};
