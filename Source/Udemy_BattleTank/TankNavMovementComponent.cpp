#include "TankNavMovementComponent.h"
#include "TankTrack.h"

void UTankNavMovementComponent::Init(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
	check(LeftTrackToSet && "Left track pointer not set!");
	LeftTrack = LeftTrackToSet;
	check(RightTrackToSet && "Right track pointer not set!");
	RightTrack = RightTrackToSet;
}

void UTankNavMovementComponent::IntendMoveForward(float Throw)
{
	if (Throw != 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s intend move forward with throw: %f"), *GetName(), Throw);
	}

	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}

void UTankNavMovementComponent::IntendRotateRight(float Throw)
{
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
}

void UTankNavMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto AIForwardIntention = MoveVelocity.GetSafeNormal();

	IntendMoveForward(FVector::DotProduct(TankForward, AIForwardIntention));
}
