#include "Enemy/Enemy.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Animation/AnimMontage.h"
#include "OdysseyOfShadows/DebugMacros.h"


AEnemy::AEnemy()
{
	PrimaryActorTick.bCanEverTick = true;

	GetMesh()->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
	GetMesh()->SetGenerateOverlapEvents(true);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
}


void AEnemy::BeginPlay()
{
	Super::BeginPlay();
}

void AEnemy::PlayHitReactMontage(const FName& sectionName)
{
	UAnimInstance* enemyAnimInstance = GetMesh()->GetAnimInstance();

	if (enemyAnimInstance && hitReactMontage)
	{
		enemyAnimInstance->Montage_Play(hitReactMontage);

		enemyAnimInstance->Montage_JumpToSection(sectionName, hitReactMontage);
	}
}


void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AEnemy::GetHit(const FVector& impactPoint)
{
	//DRAW_SPHERE_COLOR(impactPoint, FColor::Orange);

	DirectionalHitReact(impactPoint);

	if (hitSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, hitSound, impactPoint);
	}
	if (hitParticles && GetWorld())
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), hitParticles, impactPoint);
	}
}

void AEnemy::DirectionalHitReact(const FVector& impactPoint)
{
	const FVector forwrad = GetActorForwardVector();
	const FVector impactLowered(impactPoint.X, impactPoint.Y, GetActorLocation().Z);
	const FVector toHit = (impactLowered - GetActorLocation()).GetSafeNormal();

	const double cosTheta = FVector::DotProduct(forwrad, toHit);
	double theta = FMath::Acos(cosTheta);
	theta = FMath::RadiansToDegrees(theta);

	const FVector crossProduct = FVector::CrossProduct(forwrad, toHit);

	if (crossProduct.Z < 0)
	{
		theta *= -1.0f;
	}

	FName section("FromBack");

	if (theta >= -45.0f && theta < 45.0f)
	{
		section = FName("FromFront");
	}
	else if (theta >= -135.0f && theta < -45.0f)
	{
		section = FName("FromLeft");
	}
	else if (theta >= 45.0f && theta < 135.0f)
	{
		section = FName("FromRight");
	}

	PlayHitReactMontage(section);

	/*UKismetSystemLibrary::DrawDebugArrow(this, GetActorLocation(), (GetActorLocation() + crossProduct * 100.0f), 5.0f, FColor::Blue, 5.0f);

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(1, 5.0f, FColor::Green, FString::Printf(TEXT("Theta: %f"), theta));
	}

	UKismetSystemLibrary::DrawDebugArrow(this, GetActorLocation(), (GetActorLocation() + forwrad * 60.0f), 5.0f, FColor::Red, 5.0f);
	UKismetSystemLibrary::DrawDebugArrow(this, GetActorLocation(), (GetActorLocation() + toHit * 60.0f), 5.0f, FColor::Green, 5.0f);*/
}

