#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"

AProjectile::AProjectile():
	MovementComponent{ CreateDefaultSubobject<UProjectileMovementComponent>(FName("Movement Component")) }
{
	PrimaryActorTick.bCanEverTick = false;
	MovementComponent->bAutoActivate = false;
}

void AProjectile::Launch(float Speed)
{
	check(MovementComponent && "AProjectile - Movement Component is null!")
	MovementComponent->SetVelocityInLocalSpace(FVector::ForwardVector * Speed);
	MovementComponent->Activate();
}

