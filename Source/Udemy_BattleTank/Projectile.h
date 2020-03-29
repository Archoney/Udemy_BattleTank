#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class UProjectileMovementComponent;
class UParticleSystemComponent;
class UPrimitiveComponent;
class URadialForceComponent;

UCLASS()
class UDEMY_BATTLETANK_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	AProjectile();

	void BeginPlay() override;

	void Launch(float Speed);

protected:
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
			   UPrimitiveComponent* OtherComp, FVector NormalImpulse, 
			   const FHitResult& Hit);

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* CollisionMesh{ nullptr };

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UParticleSystemComponent* LaunchBlast{ nullptr };

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UParticleSystemComponent* ImpactBlast{ nullptr };

	UPROPERTY(VisibleAnywhere, Category = "Components")
	URadialForceComponent* ExplosionForce{ nullptr };

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float LifeSpan = 5.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float BaseDamage = 20.0f;

private:
	UProjectileMovementComponent* MovementComponent{ nullptr };
};
