#include "TankTrack.h"
#include "Components/PrimitiveComponent.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankTrack::BeginPlay()
{
	Super::BeginPlay();

	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::SetThrottle(float ThrottleValue)
{
	Throttle = FMath::Clamp(Throttle + ThrottleValue, -1.0f, 1.0f);
}

void UTankTrack::DriveTrack()
{
	auto ForceApplied = GetForwardVector() * MaxDrivingForce * Throttle;
	auto ForceLocation = GetComponentLocation();

	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}

void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	ApplySidewaysForce();
	DriveTrack();
	Throttle = 0.0f;
}

void UTankTrack::ApplySidewaysForce()
{
	auto SidewaysSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());
	auto CorrectionAcceleration = -SidewaysSpeed / GetWorld()->GetDeltaSeconds() * GetRightVector();

	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	auto CorrectionForceForOneTrack = CorrectionAcceleration * TankRoot->GetMass() / 2;

	auto ForceLocation = GetComponentLocation();
	TankRoot->AddForceAtLocation(CorrectionForceForOneTrack, ForceLocation);
}
