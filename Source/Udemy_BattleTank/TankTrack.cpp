#include "TankTrack.h"

void UTankTrack::SetThrottle(float Throttle)
{
	if (Throttle != 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s throttle at %f"), *GetName(), Throttle);
	}

	auto ForceApplied = GetForwardVector() * MaxDrivingForce * Throttle;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());

	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}