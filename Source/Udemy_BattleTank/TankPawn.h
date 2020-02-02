#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TankPawn.generated.h"

class UTankAimingComponent;
class UTankBarrel;
class UTankTurret;

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
		float LaunchSpeed = 100000.0f;

protected:
	UTankAimingComponent* AimingComponent{ nullptr };
};
