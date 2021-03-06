#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "SprungWheel.generated.h"

class USphereComponent;
class UPhysicsConstraintComponent;

UCLASS()
class UDEMY_BATTLETANK_API ASprungWheel : public AActor
{
	GENERATED_BODY()

public:
	ASprungWheel();

	void Tick(float DeltaSeconds) override;
	void AddDrivingForce(float Magnitude);

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

protected:
	void BeginPlay() override;

private:
	void SetupConstraints();

	UPROPERTY(VisibleAnywhere, Category = "Components")
	USphereComponent* Axle{nullptr};
	UPROPERTY(VisibleAnywhere, Category = "Components")
	USphereComponent* Wheel{nullptr};
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UPhysicsConstraintComponent* MassAxleConstraint{nullptr};
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UPhysicsConstraintComponent* AxleWheelConstraint{nullptr};

	FVector DrivingForce{};
};
