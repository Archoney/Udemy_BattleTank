#include "TankNavMovementComponent.h"
#include "TankTrack.h"

void UTankNavMovementComponent::BeginPlay()
{
	Super::BeginPlay();

	auto TankLeftTrack = GetOwner()->GetComponentsByTag(UTankTrack::StaticClass(), "LeftTrack")[0];
	check(TankLeftTrack && "UTankNavMovementComponent - LeftTrack is null!");
	auto TankRightTrack = GetOwner()->GetComponentsByTag(UTankTrack::StaticClass(), "RightTrack")[0];
	check(TankRightTrack && "UTankNavMovementComponent - RightTrack is null!");

	LeftTrack = Cast<UTankTrack>(TankLeftTrack);
	RightTrack = Cast<UTankTrack>(TankRightTrack);
}

void UTankNavMovementComponent::IntendMoveForward(float Throw)
{
	LeftTrack->SetThrottle(Throw / 2.0f);
	RightTrack->SetThrottle(Throw / 2.0f);
}

void UTankNavMovementComponent::IntendRotateRight(float Throw)
{
	LeftTrack->SetThrottle(Throw / 2.0f);
	RightTrack->SetThrottle(-Throw / 2.0f);
}

void UTankNavMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto AIForwardIntention = MoveVelocity.GetSafeNormal();

	IntendMoveForward(FVector::DotProduct(TankForward, AIForwardIntention));
	IntendRotateRight(FVector::CrossProduct(TankForward, AIForwardIntention).Z);
}