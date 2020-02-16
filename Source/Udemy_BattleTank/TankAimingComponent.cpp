#include "TankAimingComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"

void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	auto TankBarrel = GetOwner()->GetComponentByClass(UTankBarrel::StaticClass());
	check(TankBarrel && "UTankAimingComponent - Barrel is null!");
	auto TankTurret = GetOwner()->GetComponentByClass(UTankTurret::StaticClass());
	check(TankTurret && "UTankAimingComponent - Turret is null!");

	Barrel = Cast<UTankBarrel>(TankBarrel);
	Turret = Cast<UTankTurret>(TankTurret);
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
		AimDirection = TossVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
	}
}

void UTankAimingComponent::Fire()
{
	check(ProjectileBlueprint && "UTankAimingComponent - ProjectileBlueprint is null!");

	if (FiringState != FiringState::Reloading)
	{
		auto Projectile = GetWorld()->SpawnActor< AProjectile >(
			ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("BarrelEnd")),
			Barrel->GetSocketRotation(FName("BarrelEnd")));
		
		check(Projectile && "UTankAimingComponent - Projectile is null!");
		Projectile->Launch(LaunchSpeed);

		TimeSinceLastFire = 0.0f;
		FiringState = FiringState::Reloading;
	}
}

void UTankAimingComponent::Update(float DeltaSeconds)
{
	if (TimeSinceLastFire <= ReloadTimeInSeconds)
	{
		TimeSinceLastFire += DeltaSeconds;
		FiringState = FiringState::Reloading;
	}
	else if (AimDirection.Equals(Barrel->GetForwardVector(), 0.01f))
	{
		FiringState = FiringState::Locked;
	}
	else
	{
		FiringState = FiringState::Aiming;
	}
}

void UTankAimingComponent::MoveBarrelTowards(const FVector& Direction)
{
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimRotator = Direction.Rotation();
	auto DeltaRotator = AimRotator - BarrelRotator;
	FRotator DeltaRotatorWinding;
	FRotator DeltaRotatorRemainder;
	DeltaRotator.GetWindingAndRemainder(DeltaRotatorWinding, DeltaRotatorRemainder);

	Barrel->Elevate(DeltaRotatorRemainder.Pitch);
	Turret->Turn(DeltaRotatorRemainder.Yaw);
}

