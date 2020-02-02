#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTurret.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class UDEMY_BATTLETANK_API UTankTurret : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	void Turn(float RelativeSpeed);

	UPROPERTY(EditDefaultsOnly, Category = Setup)
		float MaxDegreesPerSecond = 25.0f;
};
