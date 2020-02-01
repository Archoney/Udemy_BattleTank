#include "TankAimingComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankAimingComponent::AimAt(const FVector& TargetLocation)
{
	UE_LOG(LogTemp, Warning, TEXT("%s is aiming at: %s; from: %s"),
		*GetOwner()->GetName(),
		*TargetLocation.ToString(),
		*Barrel->GetComponentLocation().ToString());
}

void UTankAimingComponent::SetBarrelReference(UStaticMeshComponent* TankBarrel)
{
	check(TankBarrel);
	Barrel = TankBarrel;
}

