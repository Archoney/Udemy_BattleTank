#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class UDEMY_BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	void Elevate(float RelativeSpeed);
	
	UPROPERTY(EditDefaultsOnly, Category = Setup)
		float MaxDegreesPerSecond = 10.0f;
	UPROPERTY(EditDefaultsOnly, Category = Setup)
		float ElevationMaxDegrees = 30.0f;
	UPROPERTY(EditDefaultsOnly, Category = Setup)
		float ElevationMinDegrees = -1.0f;
};
