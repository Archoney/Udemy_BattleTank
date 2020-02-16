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
class AProjectile;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UDEMY_BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	void BeginPlay() override;

	void AimAt(const FVector& TargetLocation);

	UFUNCTION(BlueprintCallable, Category = "Firing")
	void Fire();

	void Update(float DeltaSeconds);

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Setup")
	FiringState FiringState{ FiringState::Reloading };

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AProjectile> ProjectileBlueprint;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float LaunchSpeed = 10000.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float ReloadTimeInSeconds = 3.0f;

private:
	UTankBarrel* Barrel{ nullptr };
	UTankTurret* Turret{ nullptr };

	float TimeSinceLastFire{ 0.0f };

	void MoveBarrelTowards(const FVector& Direction);
};
