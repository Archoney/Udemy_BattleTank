#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"

#include "TankNavMovementComponent.generated.h"

class UTankTrack;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class UDEMY_BATTLETANK_API UTankNavMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()

public:
	void BeginPlay() override;
	void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;

protected:
	UFUNCTION(BlueprintCallable, Category = "Input")
	void IntendMoveForward(float Throw);

	UFUNCTION(BlueprintCallable, Category = "Input")
	void IntendRotateRight(float Throw);

private:
	UTankTrack* LeftTrack = nullptr;
	UTankTrack* RightTrack = nullptr;
};
