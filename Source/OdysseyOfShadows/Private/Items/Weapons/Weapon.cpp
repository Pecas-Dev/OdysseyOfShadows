#include "Items/Weapons/Weapon.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/SphereComponent.h"
#include "Components/BoxComponent.h"
#include "Interfaces/HitInterface.h"
#include "Characters/OdysseyOfShadowsCharacter.h"


AWeapon::AWeapon()
{
	weaponBox = CreateAbstractDefaultSubobject<UBoxComponent>(TEXT("Weapon Box"));
	weaponBox->SetupAttachment(GetRootComponent());
	weaponBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	weaponBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	weaponBox->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);

	boxTraceStart = CreateAbstractDefaultSubobject<USceneComponent>(TEXT("Box Trace Start"));
	boxTraceStart->SetupAttachment(GetRootComponent());

	boxTraceEnd = CreateAbstractDefaultSubobject<USceneComponent>(TEXT("Box Trace End"));
	boxTraceEnd->SetupAttachment(GetRootComponent());
}

void AWeapon::BeginPlay()
{
	Super::BeginPlay();

	weaponBox->OnComponentBeginOverlap.AddDynamic(this, &AWeapon::OnBoxOveralp);
}

void AWeapon::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnSphereOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
}

void AWeapon::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::OnSphereEndOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);
}

void AWeapon::OnBoxOveralp(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	const FVector start = boxTraceStart->GetComponentLocation();
	const FVector end = boxTraceEnd->GetComponentLocation();

	TArray<AActor*> actorsToIgnore;
	actorsToIgnore.Add(this);

	for (AActor* actor : ignoreActors)
	{
		actorsToIgnore.AddUnique(actor);
	}

	FHitResult boxHit;

	UKismetSystemLibrary::BoxTraceSingle(this, start, end, FVector(5.0f, 5.0f, 5.0f), boxTraceStart->GetComponentRotation(), ETraceTypeQuery::TraceTypeQuery1, false, actorsToIgnore, EDrawDebugTrace::None, boxHit, true);

	if (boxHit.GetActor())
	{
		IHitInterface* hitInterface = Cast<IHitInterface>(boxHit.GetActor());

		if (hitInterface)
		{
			hitInterface->GetHit(boxHit.ImpactPoint);
		}

		ignoreActors.AddUnique(boxHit.GetActor());
	}
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
