#include "TankTrack.h"

void UTankTrack::SetThrottle(float Throttle)
{
	if (Throttle != 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s throttle at %f"), *GetName(), Throttle);
	}
}