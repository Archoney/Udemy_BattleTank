#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"

AProjectile::AProjectile():
	MovementComponent{ CreateDefaultSubobject<UProjectileMovementComponent>(FName("Movement Component")) },
	CollisionMesh{ CreateDefaultSubobject<UStaticMeshComponent>(FName("Collision Mesh")) },
	LaunchBlast{ CreateDefaultSubobject<UParticleSystemComponent>(FName("Launch Blast")) }
{
	PrimaryActorTick.bCanEverTick = false;
	MovementComponent->bAutoActivate = false;

	SetRootComponent(CollisionMesh);
	CollisionMesh->SetNotifyRigidBodyCollision(true);
	CollisionMesh->SetVisibility(false);

	LaunchBlast->AttachTo(RootComponent);
}

void AProjectile::Launch(float Speed)
{
	check(MovementComponent && "AProjectile - Movement Component is null!")
	MovementComponent->SetVelocityInLocalSpace(FVector::ForwardVector * Speed);
	MovementComponent->Activate();
}