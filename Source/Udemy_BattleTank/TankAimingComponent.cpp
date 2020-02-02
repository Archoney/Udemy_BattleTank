#include "TankAimingComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TankBarrel.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankAimingComponent::AimAt(const FVector& TargetLocation, float LaunchSpeed)
{

	FVector TossVelocity;
	auto StartLocation = Barrel->GetSocketLocation(FName("BarrelEnd"));
	auto VelocityFound = UGameplayStatics::SuggestProjectileVelocity(
		this, TossVelocity, StartLocation, TargetLocation, LaunchSpeed, false, 0.f, 0, ESuggestProjVelocityTraceOption::DoNotTrace
		//DEBUG ,FCollisionResponseParams::DefaultResponseParam,TArray<AActor*>(),true
		);

	if (VelocityFound)
	{
		auto AimDirection = TossVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
	}
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* TankBarrel)
{
	check(TankBarrel);
	Barrel = TankBarrel;
}

void UTankAimingComponent::MoveBarrelTowards(const FVector& Direction)
{
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimRotator = Direction.Rotation();
	Barrel->Elevate(5.0f);
}

