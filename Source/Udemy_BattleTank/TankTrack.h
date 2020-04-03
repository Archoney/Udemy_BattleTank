#pragma once

#include "Components/StaticMeshComponent.h"
#include "CoreMinimal.h"

#include "TankTrack.generated.h"

class ASprungWheel;
class USpawnPoint;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class UDEMY_BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	UTankTrack();

	UFUNCTION(BlueprintCallable, Category = "Input")
	void SetThrottle(float ThrottleValue);

protected:
	UFUNCTION(BlueprintCallable, Category = "Driving")
	TArray<ASprungWheel*> GetWheels() const;

	UFUNCTION(BlueprintCallable, Category = "Driving")
	TArray<USpawnPoint*> GetSpawnPoints() const;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float MaxDrivingForce = 80000000.0f;

private:
	void DriveTrack(float Throttle);
};
