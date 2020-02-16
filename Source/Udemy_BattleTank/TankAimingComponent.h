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

	void InitBarrel(UTankBarrel* TankBarrel);
	void InitTurret(UTankTurret* TankTurret);

	void AimAt(const FVector& TargetLocation, float LaunchSpeed);

	UTankBarrel* GetBarrel() const;

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Setup")
	FiringState FiringState{ FiringState::Reloading };

private:
	void MoveBarrelTowards(const FVector& Direction);

	UTankBarrel* Barrel{ nullptr };
	UTankTurret* Turret{ nullptr };
};
