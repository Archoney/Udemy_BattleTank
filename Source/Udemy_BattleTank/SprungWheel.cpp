#include "SprungWheel.h"

#include "Components/SphereComponent.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"

ASprungWheel::ASprungWheel()
	: MassAxleConstraint{CreateDefaultSubobject<UPhysicsConstraintComponent>(
		  FName("Mass Axle Constraint"))}
	, AxleWheelConstraint{CreateDefaultSubobject<UPhysicsConstraintComponent>(
		  FName("Axle Wheel Constraint"))}
	, Axle{CreateDefaultSubobject<USphereComponent>(FName("Axle"))}
	, Wheel{CreateDefaultSubobject<USphereComponent>(FName("Wheel"))}
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickGroup = TG_PostPhysics;

	SetRootComponent(MassAxleConstraint);
	Axle->SetupAttachment(MassAxleConstraint);
	AxleWheelConstraint->SetupAttachment(Axle);
	Wheel->SetupAttachment(AxleWheelConstraint);
}

void ASprungWheel::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (GetWorld()->TickGroup == TG_PostPhysics)
	{
		DrivingForce = FVector{};
	}
}

void ASprungWheel::AddDrivingForce(float Magnitude)
{
	DrivingForce += Magnitude * Axle->GetForwardVector();
}

void ASprungWheel::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	Axle->AddForce(DrivingForce);
}

void ASprungWheel::BeginPlay()
{
	Super::BeginPlay();

	Wheel->SetNotifyRigidBodyCollision(true);
	Wheel->OnComponentHit.AddDynamic(this, &ASprungWheel::OnHit);

	SetupConstraints();
}

void ASprungWheel::SetupConstraints()
{
	auto TankMesh = Cast<UPrimitiveComponent>(GetAttachParentActor()->GetRootComponent());
	MassAxleConstraint->SetConstrainedComponents(
		TankMesh, FName(), Cast<UPrimitiveComponent>(Axle), FName());
	AxleWheelConstraint->SetConstrainedComponents(Cast<UPrimitiveComponent>(Axle),
		FName(), Cast<UPrimitiveComponent>(Wheel), FName());
}
