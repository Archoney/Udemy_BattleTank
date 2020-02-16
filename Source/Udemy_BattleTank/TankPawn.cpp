#include "TankPawn.h"
#include "TankAimingComponent.h"
#include "TankNavMovementComponent.h"
#include "Engine/World.h"
#include "TankBarrel.h"
#include "Projectile.h"

ATankPawn::ATankPawn()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ATankPawn::BeginPlay()
{
	Super::BeginPlay();
	LastFireTime = FPlatformTime::Seconds();
}

void ATankPawn::AimAt(const FVector& TargetLocation)
{
	check(AimingComponent && "ATankPawn - AimingComponent pointer is null!");
	AimingComponent->AimAt(TargetLocation, LaunchSpeed);
}

void ATankPawn::Fire()
{
	check(AimingComponent && "ATankPawn - AimingComponent pointer is null!");
	bool isReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;
	if (isReloaded)
	{
		auto Projectile = GetWorld()->SpawnActor< AProjectile >(
			ProjectileBlueprint,
			AimingComponent->GetBarrel()->GetSocketLocation(FName("BarrelEnd")),
			AimingComponent->GetBarrel()->GetSocketRotation(FName("BarrelEnd")));

		Projectile->Launch(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
	}
}

void ATankPawn::InitAimingComponent(UTankAimingComponent* TankAimingComponent, 
									UTankBarrel* TankBarrel, 
									UTankTurret* TankTurret)
{
	check(TankAimingComponent && "ATankPawn - Aiming component pointer is null!");
	check(TankBarrel && "ATankPawn - Barrel pointer is null!");
	check(TankTurret && "ATankPawn - Turret pointer is null!");

	AimingComponent = TankAimingComponent;
	AimingComponent->InitBarrel(TankBarrel);
	AimingComponent->InitTurret(TankTurret);
}

void ATankPawn::InitMovementComponent(UTankNavMovementComponent* TankMovementComponent,
									  UTankTrack* TankLeftTrack, 
									  UTankTrack* TankRightTrack)
{
	check(TankMovementComponent && "ATankPawn - Movement component pointer is null!");
	check(TankLeftTrack && "ATankPawn - Left Track pointer is null!");
	check(TankRightTrack && "ATankPawn - Right Track pointer is null!");

	MovementComponent = TankMovementComponent;
	MovementComponent->InitTracks(TankLeftTrack, TankRightTrack);
}
