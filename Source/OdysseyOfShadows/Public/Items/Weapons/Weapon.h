// Fill out your copyright notice in the Description page of Project Settings.

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

	void Equip(USceneComponent* inParent, FName inSocketName);

	void AttachMeshToSocket(USceneComponent* inParent, const FName& inSocketName);

protected:
	virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	virtual void OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;


private:

};
