#include "TankAimingComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"

void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	auto TankPawn = GetOwner();
	check(TankPawn && "UTankAimingComponent - Owner is null!");
	auto TankBarrel = TankPawn->GetComponentByClass(UTankBarrel::StaticClass());
	check(TankBarrel && "UTankAimingComponent - Barrel is null!");
	auto TankTurret = TankPawn->GetComponentByClass(UTankTurret::StaticClass());
	check(TankTurret && "UTankAimingComponent - Turret is null!");

	Barrel = Cast<UTankBarrel>(TankBarrel);
	Turret = Cast<UTankTurret>(TankTurret);

	LastFireTime = FPlatformTime::Seconds();
}

void UTankAimingComponent::AimAt(const FVector& TargetLocation)
{
	FVector TossVelocity;
	auto StartLocation = Barrel->GetSocketLocation(FName("BarrelEnd"));
	auto VelocityFound = UGameplayStatics::SuggestProjectileVelocity(
		this, TossVelocity, StartLocation, TargetLocation, LaunchSpeed, 
		false, 0.f, 0, ESuggestProjVelocityTraceOption::DoNotTrace);

	if (VelocityFound)
	{
		auto AimDirection = TossVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
	}
}

void UTankAimingComponent::Fire()
{
	check(ProjectileBlueprint && "UTankAimingComponent - ProjectileBlueprint is null!");

	bool isReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;
	if (isReloaded)
	{
		auto Projectile = GetWorld()->SpawnActor< AProjectile >(
			ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("BarrelEnd")),
			Barrel->GetSocketRotation(FName("BarrelEnd")));
		
		check(Projectile && "UTankAimingComponent - Projectile is null!");
		Projectile->Launch(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
	}
}

void UTankAimingComponent::MoveBarrelTowards(const FVector& Direction)
{
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimRotator = Direction.Rotation();
	auto DeltaRotator = AimRotator - BarrelRotator;

	Barrel->Elevate(DeltaRotator.Pitch);
	Turret->Turn(DeltaRotator.Yaw);
}

