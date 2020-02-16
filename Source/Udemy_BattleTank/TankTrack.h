#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class UDEMY_BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	UTankTrack();

	UFUNCTION(BlueprintCallable, Category = "Input")
	void SetThrottle(float Throttle);	
	
	void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(BlueprintReadWrite, Category = "Moving")
	bool IsOnGround{false};

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float MaxDrivingForce = 50000000.0f;
};
