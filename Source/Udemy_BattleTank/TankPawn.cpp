#include "TankPawn.h"
#include "TankAimingComponent.h"
#include "Engine/World.h"
#include "TankBarrel.h"
#include "Projectile.h"

// Sets default values
ATankPawn::ATankPawn() 
	: AimingComponent{ CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component")) }
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void ATankPawn::AimAt(const FVector& TargetLocation)
{
	AimingComponent->AimAt(TargetLocation, LaunchSpeed);
}

void ATankPawn::SetBarrelReference(UTankBarrel* TankBarrel)
{
	Barrel = TankBarrel;
	AimingComponent->SetBarrelReference(TankBarrel);
}

void ATankPawn::SetTurretReference(UTankTurret* TankTurret)
{
	AimingComponent->SetTurretReference(TankTurret);
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

