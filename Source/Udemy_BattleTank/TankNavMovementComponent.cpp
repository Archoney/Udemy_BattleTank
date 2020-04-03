#include "TankNavMovementComponent.h"

#include "DrawDebugHelpers.h"
#include "TankTrack.h"

void UTankNavMovementComponent::BeginPlay()
{
	Super::BeginPlay();

	auto TankTracks = GetOwner()->GetComponentsByClass(UTankTrack::StaticClass());
	for (auto Track : TankTracks)
	{
		if (Track->GetName() == TEXT("IS4_track_L"))
		{
			LeftTrack = Cast<UTankTrack>(Track);
		}
		if (Track->GetName() == TEXT("IS4_track_R"))
		{
			RightTrack = Cast<UTankTrack>(Track);
		}
	}

	check(LeftTrack && "UTankNavMovementComponent - LeftTrack is null!");
	check(RightTrack && "UTankNavMovementComponent - RightTrack is null!");
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

void UTankNavMovementComponent::RequestDirectMove(
	const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	Super::RequestDirectMove(MoveVelocity, bForceMaxSpeed);

	auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal2D();
	auto AIForwardIntention = MoveVelocity.GetSafeNormal2D();

	// DrawDebugLine(GetWorld(), GetOwner()->GetActorLocation(),
	// GetOwner()->GetActorLocation() + 10000.0 * AIForwardIntention, FColor::Red, false,
	// -1.0f, 0, 100.0f);

	auto RotateIntent = FVector::CrossProduct(TankForward, AIForwardIntention).Z;
	auto ForwardIntent = FVector::DotProduct(TankForward, AIForwardIntention);

	IntendRotateRight(RotateIntent);
	IntendMoveForward(ForwardIntent);
}