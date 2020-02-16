#include "TankTrack.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankTrack::SetThrottle(float Throttle)
{
	if (IsOnGround)
	{
		auto ForceApplied = GetForwardVector() * MaxDrivingForce * Throttle;
		auto ForceLocation = GetComponentLocation();

		auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
		TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
	}
}

void UTankTrack::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	IsOnGround = FMath::Abs(GetComponentVelocity().Z) <= 100.0f;

	if (IsOnGround)
	{
		auto SidewaysSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());
		auto CorrectionAcceleration = -SidewaysSpeed / DeltaTime * GetRightVector();

		auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
		auto CorrectionForceForOneTrack = CorrectionAcceleration * TankRoot->GetMass() / 2;

		auto ForceLocation = GetComponentLocation();
		TankRoot->AddForceAtLocation(CorrectionForceForOneTrack, ForceLocation);
	}
}
