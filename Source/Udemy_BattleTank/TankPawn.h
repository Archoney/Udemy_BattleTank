#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TankPawn.generated.h"

class UTankAimingComponent;
class UTankBarrel;
class UTankTurret;
class AProjectile;

UCLASS()
class UDEMY_BATTLETANK_API ATankPawn : public APawn
{
	GENERATED_BODY()

public:
	ATankPawn();

	void AimAt(const FVector& TargetLocation);

	UFUNCTION(BlueprintCallable, Category = Setup)
		void SetBarrelReference(UTankBarrel* TankBarrel);

	UFUNCTION(BlueprintCallable, Category = Setup)
		void SetTurretReference(UTankTurret* TankTurret);

	UPROPERTY(EditAnywhere, Category = Setup)
		TSubclassOf<AProjectile> ProjectileBlueprint;

	UFUNCTION(BlueprintCallable, Category = Firing)
		void Fire();

	UPROPERTY(EditAnywhere, Category = Firing)
		float LaunchSpeed = 10000.0f;

protected:
	UTankAimingComponent* AimingComponent{ nullptr };

private:
	UTankBarrel* Barrel{ nullptr };
};
