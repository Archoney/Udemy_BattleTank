#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UDEMY_BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UTankAimingComponent();

public:	
	void AimAt(const FVector& TargetLocation);
	void SetBarrelReference(UStaticMeshComponent* TankBarrel);

private:
	UStaticMeshComponent* Barrel{ nullptr };
};
