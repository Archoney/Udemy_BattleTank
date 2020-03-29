#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"

AProjectile::AProjectile():
	CollisionMesh{ CreateDefaultSubobject<UStaticMeshComponent>(FName("Collision Mesh")) },
	LaunchBlast{ CreateDefaultSubobject<UParticleSystemComponent>(FName("Launch Blast")) },
	ImpactBlast{ CreateDefaultSubobject<UParticleSystemComponent>(FName("Impact Blast")) },
	MovementComponent{ CreateDefaultSubobject<UProjectileMovementComponent>(FName("Movement Component")) }
{
	PrimaryActorTick.bCanEverTick = false;

	SetRootComponent(CollisionMesh);
	CollisionMesh->SetNotifyRigidBodyCollision(true);
	CollisionMesh->SetVisibility(false);

	LaunchBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	ImpactBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	ImpactBlast->bAutoActivate = false;

	MovementComponent->bAutoActivate = false;
}

void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	CollisionMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
}

void AProjectile::Launch(float Speed)
{
	check(MovementComponent && "AProjectile - Movement Component is null!")
	MovementComponent->SetVelocityInLocalSpace(FVector::ForwardVector * Speed);
	MovementComponent->Activate();
}

void AProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	LaunchBlast->Deactivate();
	ImpactBlast->Activate();
}
