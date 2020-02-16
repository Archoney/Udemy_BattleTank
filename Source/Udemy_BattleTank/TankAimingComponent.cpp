#include "TankAimingComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TankBarrel.h"
#include "TankTurret.h"

UTankAimingComponent::UTankAimingComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankAimingComponent::AimAt(const FVector& TargetLocation, float LaunchSpeed)
{
	FVector TossVelocity;
	auto StartLocation = Barrel->GetSocketLocation(FName("BarrelEnd"));
	auto VelocityFound = UGameplayStatics::SuggestProjectileVelocity(
		this, TossVelocity, StartLocation, TargetLocation, LaunchSpeed, false, 0.f, 0, ESuggestProjVelocityTraceOption::DoNotTrace);

	if (VelocityFound)
	{
		auto AimDirection = TossVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
	}
}

UTankBarrel* UTankAimingComponent::GetBarrel() const
{
	check(Barrel && "UTankAimingComponent - Barrel is null!");
	return Barrel;
}

void UTankAimingComponent::InitBarrel(UTankBarrel* TankBarrel)
{
	check(TankBarrel && "UTankAimingComponent - Barrel is null!");
	Barrel = TankBarrel;
}

void UTankAimingComponent::InitTurret(UTankTurret* TankTurret)
{
	check(TankTurret && "UTankAimingComponent - Turret is null!");
	Turret = TankTurret;
}

void UTankAimingComponent::MoveBarrelTowards(const FVector& Direction)
{
	check(Barrel && "UTankAimingComponent - Barrel is null!");
	check(Turret && "UTankAimingComponent - Turret is null!");

	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimRotator = Direction.Rotation();
	auto DeltaRotator = AimRotator - BarrelRotator;

	Barrel->Elevate(DeltaRotator.Pitch);
	Turret->Turn(DeltaRotator.Yaw);
}

