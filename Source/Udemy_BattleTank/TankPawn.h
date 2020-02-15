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

	void BeginPlay() override;

	void AimAt(const FVector& TargetLocation);

	UPROPERTY(EditDefaultsOnly, Category = Setup)
		TSubclassOf<AProjectile> ProjectileBlueprint;

	UFUNCTION(BlueprintCallable, Category = Setup)
		void InitAimingComponent(UTankAimingComponent* AimingComponentToSet);

	UFUNCTION(BlueprintCallable, Category = Setup)
		void InitBarrel(UTankBarrel* BarrelToSet);

	UFUNCTION(BlueprintCallable, Category = Firing)
		void Fire();

	UPROPERTY(EditDefaultsOnly, Category = Firing)
		float LaunchSpeed = 10000.0f;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
		float ReloadTimeInSeconds = 3.0f;

private:
	UTankAimingComponent* AimingComponent{nullptr};
	UTankBarrel* Barrel{ nullptr };
	double LastFireTime{ 0.0 };
};
