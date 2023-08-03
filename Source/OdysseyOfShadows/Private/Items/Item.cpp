#include "Items/Item.h"
#include "OdysseyOfShadows/DebugMacros.h"


AItem::AItem()
{
	PrimaryActorTick.bCanEverTick = true;

	itemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMeshComponent"));
	RootComponent = itemMesh;
}

void AItem::BeginPlay()
{
	Super::BeginPlay();
}

float AItem::TransformedSine()
{
	return amplitude * FMath::Sin(runningTime * timeConstant);
}

float AItem::TransformedCosine()
{
	return amplitude * FMath::Cos(runningTime * timeConstant);
}

void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	runningTime += DeltaTime;

	FRotator rotation = FRotator(rotationConstantX, rotationConstantY, 0.f);

	AddActorWorldRotation(rotation);
}

