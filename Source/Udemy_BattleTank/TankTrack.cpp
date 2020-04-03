#include "TankTrack.h"

#include "Components/PrimitiveComponent.h"
#include "SpawnPoint.h"
#include "SprungWheel.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankTrack::SetThrottle(float ThrottleValue)
{
	auto Throttle = FMath::Clamp(ThrottleValue, -1.0f, 1.0f);
	DriveTrack(Throttle);
}

TArray<ASprungWheel*> UTankTrack::GetWheels() const
{
	TArray<ASprungWheel*> Wheels;
	auto SpawnPoints = GetSpawnPoints();

	for (auto SpawnPoint : SpawnPoints)
	{
		auto Wheel = Cast<ASprungWheel>(SpawnPoint->GetSpawnedActor());
		if (Wheel)
		{
			Wheels.Add(Wheel);
		}
	}

	return Wheels;
}

TArray<USpawnPoint*> UTankTrack::GetSpawnPoints() const
{
	TArray<USpawnPoint*> SpawnPoints;
	TArray<USceneComponent*> Children;
	GetChildrenComponents(false, Children);

	for (auto Child : Children)
	{
		auto SpawnPoint = Cast<USpawnPoint>(Child);
		if (SpawnPoint)
		{
			SpawnPoints.Add(SpawnPoint);
		}
	}

	return SpawnPoints;
}

void UTankTrack::DriveTrack(float Throttle)
{
	auto Wheels = GetWheels();
	if (Wheels.Num() > 0)
	{
		auto Magnitude = MaxDrivingForce * Throttle;
		auto ForcePerWheel = Magnitude / Wheels.Num();

		for (auto Wheel : Wheels)
		{
			Wheel->AddDrivingForce(ForcePerWheel);
		}
	}
}