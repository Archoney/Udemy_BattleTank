#pragma once

#include "Components/StaticMeshComponent.h"
#include "CoreMinimal.h"

#include "TankBarrel.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class UDEMY_BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	void Elevate(float RelativeSpeed);

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float MaxDegreesPerSecond = 10.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float ElevationMaxDegrees = 15.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float ElevationMinDegrees = -2.0f;
};
