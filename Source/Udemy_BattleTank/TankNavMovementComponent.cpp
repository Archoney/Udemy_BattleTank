#include "TankNavMovementComponent.h"

void UTankNavMovementComponent::IntendMoveForward(float Throw)
{
	if (Throw != 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s intend move forward with throw: %f"), *GetName(), Throw);
	}
}