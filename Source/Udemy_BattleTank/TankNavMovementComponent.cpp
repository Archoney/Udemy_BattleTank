#include "TankNavMovementComponent.h"
#include "TankTrack.h"

void UTankNavMovementComponent::IntendMoveForward(float Throw)
{
	check(LeftTrack && "UTankNavMovementComponent - Left track is null!");
	check(RightTrack && "UTankNavMovementComponent - Right track is null!");

	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}

void UTankNavMovementComponent::IntendRotateRight(float Throw)
{
	check(LeftTrack && "UTankNavMovementComponent - Left track is null!");
	check(RightTrack && "UTankNavMovementComponent - Right track is null!");

	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
}

void UTankNavMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto AIForwardIntention = MoveVelocity.GetSafeNormal();

	IntendMoveForward(FVector::DotProduct(TankForward, AIForwardIntention));
	IntendRotateRight(FVector::CrossProduct(TankForward, AIForwardIntention).Z);
}

void UTankNavMovementComponent::InitTracks(UTankTrack* TankLeftTrack, UTankTrack* TankRightTrack)
{
	check(TankLeftTrack && "UTankNavMovementComponent - Left track is null!");
	check(TankRightTrack && "UTankNavMovementComponent - Right track is null!");

	LeftTrack = TankLeftTrack;
	RightTrack = TankRightTrack;
}