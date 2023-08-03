#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
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

	UFUNCTION(BlueprintPure)
		float TransformedSine();

	UFUNCTION(BlueprintPure)
		float TransformedCosine();

	template<typename T>
	T Avarage(T first, T second);

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		float runningTime;

	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* itemMesh;
};

template<typename T>
inline T AItem::Avarage(T first, T second)
{
	return (first + second) / 2;
}
