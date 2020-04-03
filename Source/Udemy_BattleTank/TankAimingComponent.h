#pragma once

#include "Components/ActorComponent.h"
#include "CoreMinimal.h"

#include "TankAimingComponent.generated.h"

UENUM()
enum class FiringState : uint8
{
	Reloading,
	Aiming,
	Locked,
	NoAmmo
};

class UTankBarrel;
class UTankTurret;
class AProjectile;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class UDEMY_BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UTankAimingComponent();

	void BeginPlay() override;

	void AimAt(const FVector& TargetLocation);

	UFUNCTION(BlueprintCallable, Category = "Firing")
	void Fire();

	void TickComponent(float DeltaTime, enum ELevelTick TickType,
		FActorComponentTickFunction* ThisTickFunction) override;

	bool IsLocked() const;

	UFUNCTION()
	void OnTankDestroyed();

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Setup")
	FiringState FiringState{FiringState::Reloading};

	UPROPERTY(BlueprintReadWrite, Category = "Setup")
	TSubclassOf<AProjectile> ProjectileBlueprint;

	UPROPERTY(BlueprintReadWrite, Category = "Firing")
	uint8 Ammo = 20;

	UPROPERTY(BlueprintReadWrite, Category = "Firing")
	float LaunchSpeed = 10000.0f;

	UPROPERTY(BlueprintReadWrite, Category = "Firing")
	float ReloadTimeInSeconds = 2.0f;

	UPROPERTY(BlueprintReadWrite, Category = "Firing")
	bool HighArc = false;

private:
	UTankBarrel* Barrel{nullptr};
	UTankTurret* Turret{nullptr};

	float TimeSinceLastFire{0.0f};

	void MoveBarrelTowards(const FVector& Direction);
	FVector AimDirection;
};
