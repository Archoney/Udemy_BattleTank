#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

UENUM()
enum class FiringState : uint8
{
	Reloading,
	Aiming,
	Ready
};

class UTankBarrel;
class UTankTurret;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UDEMY_BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UTankAimingComponent();

public:	
	UFUNCTION(BlueprintCallable, Category = "Firing")
		void AimAt(const FVector& TargetLocation, float LaunchSpeed);
	UFUNCTION(BlueprintCallable, Category = "Setup")
		void SetBarrelReference(UTankBarrel* TankBarrel);
	UFUNCTION(BlueprintCallable, Category = "Setup")
		void SetTurretReference(UTankTurret* TankTurret);

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Setup")
	FiringState FiringState{ FiringState::Reloading };


private:
	void MoveBarrelTowards(const FVector& Direction);

	UTankBarrel* Barrel{ nullptr };
	UTankTurret* Turret{ nullptr };
};
