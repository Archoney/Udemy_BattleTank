#include "TankTurret.h"

void UTankTurret::Turn(float RelativeSpeed)
{
	auto ClampedRelaticeSpeed = FMath::Clamp(RelativeSpeed, -1.0f, 1.0f);
	auto TurningChange =
		ClampedRelaticeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto Yaw = RelativeRotation.Yaw + TurningChange;
	SetRelativeRotation(FRotator(0.0f, Yaw, 0.0f));
}