#include "Projectile.h"

#include "Components/PrimitiveComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine//World.h"
#include "GameFramework/DamageType.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "TimerManager.h"

AProjectile::AProjectile()
	: CollisionMesh{CreateDefaultSubobject<UStaticMeshComponent>(FName("Collision Mesh"))}
	, LaunchBlast{CreateDefaultSubobject<UParticleSystemComponent>(FName("Launch Blast"))}
	, ImpactBlast{CreateDefaultSubobject<UParticleSystemComponent>(FName("Impact Blast"))}
	, ExplosionForce{CreateDefaultSubobject<URadialForceComponent>(
		  FName("Explosion Force"))}
	, MovementComponent{CreateDefaultSubobject<UProjectileMovementComponent>(
		  FName("Movement Component"))}
{
	PrimaryActorTick.bCanEverTick = false;

	SetRootComponent(CollisionMesh);
	CollisionMesh->SetNotifyRigidBodyCollision(true);
	CollisionMesh->SetVisibility(false);

	LaunchBlast->SetupAttachment(CollisionMesh);

	ImpactBlast->SetupAttachment(CollisionMesh);
	ImpactBlast->bAutoActivate = false;

	ExplosionForce->SetupAttachment(CollisionMesh);

	MovementComponent->bAutoActivate = false;
}

void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	CollisionMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
	SetLifeSpan(LifeSpan);
}

void AProjectile::Launch(float Speed)
{
	check(MovementComponent && "AProjectile - Movement Component is null!")
		MovementComponent->SetVelocityInLocalSpace(FVector::ForwardVector * Speed);
	MovementComponent->Activate();
}

void AProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	LaunchBlast->Deactivate();
	ImpactBlast->Activate();
	ExplosionForce->FireImpulse();
	UGameplayStatics::ApplyRadialDamage(this, BaseDamage, GetActorLocation(),
		ExplosionForce->Radius, UDamageType::StaticClass(), TArray<AActor*>());

	SetRootComponent(ImpactBlast);
	CollisionMesh->DestroyComponent();
}
