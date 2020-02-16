#include "TankPawn.h"
#include "TankAimingComponent.h"
#include "Engine/World.h"
#include "TankBarrel.h"
#include "Projectile.h"

// Sets default values
ATankPawn::ATankPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void ATankPawn::BeginPlay()
{
	Super::BeginPlay();
	LastFireTime = FPlatformTime::Seconds();
}

void ATankPawn::AimAt(const FVector& TargetLocation)
{
	AimingComponent->AimAt(TargetLocation, LaunchSpeed);
}

void ATankPawn::InitAimingComponent(UTankAimingComponent* AimingComponentToSet)
{
	check(AimingComponentToSet && "Aiming component pointer is null!");
	AimingComponent = AimingComponentToSet;
}

UTankAimingComponent* ATankPawn::GetAimingComponent() const
{
	return AimingComponent;
}

void ATankPawn::InitBarrel(UTankBarrel* BarrelToSet)
{
	check(BarrelToSet && "Barrel pointer is null!");
	Barrel = BarrelToSet;
}

void ATankPawn::Fire()
{
	bool isReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;

	if (isReloaded)
	{
		auto Projectile = GetWorld()->SpawnActor< AProjectile >(
			ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("BarrelEnd")),
			Barrel->GetSocketRotation(FName("BarrelEnd")));

		Projectile->Launch(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
	}
}

