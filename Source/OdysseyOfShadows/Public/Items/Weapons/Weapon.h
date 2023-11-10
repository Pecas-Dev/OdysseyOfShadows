#pragma once

#include "CoreMinimal.h"
#include "Items/Item.h"
#include "Weapon.generated.h"

/**
 *
 */
UCLASS()
class ODYSSEYOFSHADOWS_API AWeapon : public AItem
{


	GENERATED_BODY()

public:

	AWeapon();

	void Equip(USceneComponent* inParent, FName inSocketName);

	void AttachMeshToSocket(USceneComponent* inParent, const FName& inSocketName);


	TArray<AActor*> ignoreActors;


protected:
	virtual void BeginPlay() override;

	virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	virtual void OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;

	UFUNCTION()
	void OnBoxOveralp(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


private:

	UPROPERTY(EditAnywhere, Category = WeaponProperty)
	class USoundBase* equipBladeSound;

	UPROPERTY(VisibleAnywhere, Category = WeaponProperty)
	class UBoxComponent* weaponBox;

	UPROPERTY(VisibleAnywhere)
	class USceneComponent* boxTraceStart;

	UPROPERTY(VisibleAnywhere)
	class USceneComponent* boxTraceEnd;


public:

	FORCEINLINE UBoxComponent* GetWeaponBox() const { return weaponBox; }
};
