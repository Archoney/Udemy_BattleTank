#include "TankBarrel.h"

void UTankBarrel::Elevate(float RelativeSpeed)
{
	auto ClampedRelaticeSpeed = FMath::Clamp(RelativeSpeed, -1.0f, 1.0f);
	auto ElevationChange = ClampedRelaticeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto ClampedPitch = FMath::Clamp(GetRelativeRotation().Pitch + ElevationChange, ElevationMinDegrees, ElevationMaxDegrees);
	SetRelativeRotation(FRotator(ClampedPitch, 0.0f, 0.0f));
}