#include "Items/Item.h"
#include "Components/SphereComponent.h"
#include "Characters/OdysseyOfShadowsCharacter.h"
#include "OdysseyOfShadows/DebugMacros.h"


AItem::AItem()
{
	PrimaryActorTick.bCanEverTick = true;

	itemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMeshComponent"));
	RootComponent = itemMesh;

	sphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	sphereComponent->SetupAttachment(GetRootComponent());
}

void AItem::BeginPlay()
{
	Super::BeginPlay();

	sphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AItem::OnSphereOverlap);
	sphereComponent->OnComponentEndOverlap.AddDynamic(this, &AItem::OnSphereEndOverlap);
}

float AItem::TransformedSine()
{
	return amplitude * FMath::Sin(runningTime * timeConstant);
}

float AItem::TransformedCosine()
{
	return amplitude * FMath::Cos(runningTime * timeConstant);
}

void AItem::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AOdysseyOfShadowsCharacter* oddyseyOfShadowsCharacter = Cast<AOdysseyOfShadowsCharacter>(OtherActor);

	if (oddyseyOfShadowsCharacter)
	{
		oddyseyOfShadowsCharacter->SetOverlappingItem(this);
	}
}

void AItem::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AOdysseyOfShadowsCharacter* oddyseyOfShadowsCharacter = Cast<AOdysseyOfShadowsCharacter>(OtherActor);

	if (oddyseyOfShadowsCharacter)
	{
		oddyseyOfShadowsCharacter->SetOverlappingItem(nullptr);
	}
}

void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	runningTime += DeltaTime;

	if (itemState == EItemState::EIS_Hovering)
	{
		AddActorWorldOffset(FVector(0.f, 0.f, TransformedSine()));
	}
}

