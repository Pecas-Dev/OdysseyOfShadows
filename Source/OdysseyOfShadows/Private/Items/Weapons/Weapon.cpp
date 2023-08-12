#include "Kismet/GameplayStatics.h"
#include "Components/SphereComponent.h"
#include "Characters/OdysseyOfShadowsCharacter.h"
#include "Items/Weapons/Weapon.h"


void AWeapon::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnSphereOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
}

void AWeapon::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::OnSphereEndOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);
}

void AWeapon::Equip(USceneComponent* inParent, FName inSocketName)
{
	AttachMeshToSocket(inParent, inSocketName);

	itemState = EItemState::EIS_Equipped;

	if (equipBladeSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, equipBladeSound, GetActorLocation());
	}
	if (sphereComponent)
	{
		sphereComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

void AWeapon::AttachMeshToSocket(USceneComponent* inParent, const FName& inSocketName)
{
	FAttachmentTransformRules TransformRules(EAttachmentRule::SnapToTarget, true);

	itemMesh->AttachToComponent(inParent, TransformRules, inSocketName);
}
