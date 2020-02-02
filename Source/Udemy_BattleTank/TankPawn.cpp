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
	UE_LOG(LogTemp, Warning, TEXT("%s Fires!"), *GetName());

	GetWorld()->SpawnActor< AProjectile >(
		ProjectileBlueprint,
		Barrel->GetSocketLocation(FName("Barrel")),
		Barrel->GetSocketRotation(FName("Barrel")));
}

