#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

class UTankBarrel;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UDEMY_BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UTankAimingComponent();

public:	
	void AimAt(const FVector& TargetLocation, float LaunchSpeed);
	void SetBarrelReference(UTankBarrel* TankBarrel);

private:
	UTankBarrel* Barrel{ nullptr };
	void MoveBarrelTowards(const FVector& Direction);
};
