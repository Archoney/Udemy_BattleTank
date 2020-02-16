#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TankPawn.generated.h"

class UTankAimingComponent;
class UTankNavMovementComponent;
class UTankBarrel;
class UTankTurret;
class UTankTrack;
class AProjectile;

UCLASS()
class UDEMY_BATTLETANK_API ATankPawn : public APawn
{
	GENERATED_BODY()

public:
	ATankPawn();

	void BeginPlay() override;

	void AimAt(const FVector& TargetLocation);

	UFUNCTION(BlueprintCallable, Category = "Firing")
	void Fire();

	UTankAimingComponent* GetAimingComponent() const;

protected:
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void InitAimingComponent(UTankAimingComponent* TankAimingComponent,
							 UTankBarrel* TankBarrel, 
							 UTankTurret* TankTurret);

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void InitMovementComponent(UTankNavMovementComponent* TankMovementComponent,
							   UTankTrack* TankLeftTrack, 
							   UTankTrack* TankRightTrack);

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AProjectile> ProjectileBlueprint;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float LaunchSpeed = 10000.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float ReloadTimeInSeconds = 3.0f;

private:
	UTankAimingComponent* AimingComponent{ nullptr };
	UTankNavMovementComponent* MovementComponent{ nullptr };
	double LastFireTime{ 0.0 };
};
