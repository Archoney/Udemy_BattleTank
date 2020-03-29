#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

class ATankPawn;
class UTankAimingComponent;

UCLASS()
class UDEMY_BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	void BeginPlay() override;
	void Tick(float DeltaSeconds) override;
	void SetPawn(APawn* InPawn) override;

	UFUNCTION()
	void OnTankDestroyed();

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float FollowRadiusFromPlayer = 8000.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	bool CanFire = true;

private:
	UTankAimingComponent* AimingComponent{ nullptr };
	APawn* PlayerTank{ nullptr };
};
