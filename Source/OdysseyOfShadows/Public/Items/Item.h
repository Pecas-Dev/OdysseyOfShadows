#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemType.h"
#include "Item.generated.h"

UCLASS()
class ODYSSEYOFSHADOWS_API AItem : public AActor
{
	GENERATED_BODY()

public:
	AItem();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sine Parameters")
	float amplitude = 0.25f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sine Parameters")
	float timeConstant = 5.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rotation")
	float rotationConstantX = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rotation")
	float rotationConstantY = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rotation")
	float rotationConstantZ = 1.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* itemMesh;

	UPROPERTY(VisibleAnywhere)
	class USphereComponent* sphereComponent;

	UFUNCTION(BlueprintPure)
	float TransformedSine();

	UFUNCTION(BlueprintPure)
	float TransformedCosine();

	UFUNCTION()
	virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


	EItemState itemState = EItemState::EIS_Hovering;


	template<typename T>
	T Avarage(T first, T second);

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float runningTime;
};

template<typename T>
inline T AItem::Avarage(T first, T second)
{
	return (first + second) / 2;
}
