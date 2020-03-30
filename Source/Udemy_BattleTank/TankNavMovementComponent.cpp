#include "TankNavMovementComponent.h"
#include "TankTrack.h"
#include "DrawDebugHelpers.h"

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
	Super::RequestDirectMove(MoveVelocity, bForceMaxSpeed);

	auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal2D();
	auto AIForwardIntention = MoveVelocity.GetSafeNormal2D();

	//DrawDebugLine(GetWorld(), GetOwner()->GetActorLocation(), GetOwner()->GetActorLocation() + 10000.0 * AIForwardIntention, FColor::Red, false, -1.0f, 0, 100.0f);

	auto RotateIntent = FVector::CrossProduct(TankForward, AIForwardIntention).Z;
	auto ForwardIntent = FVector::DotProduct(TankForward, AIForwardIntention);

	IntendRotateRight(RotateIntent);
	IntendMoveForward(ForwardIntent);
}