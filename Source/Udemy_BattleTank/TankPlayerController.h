#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class ATankPawn;
class UTankAimingComponent;

UCLASS()
class UDEMY_BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	void Tick(float DeltaSeconds) override;
	void AimAtCrosshair();

	UFUNCTION(BlueprintCallable, Category = "Setup")
	ATankPawn* GetControlledTank() const;

	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
	void AimingComponentReady(UTankAimingComponent* AimingComponent);

protected:
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void SetCrosshairPositionOnCanvas(const FVector2D& Position);

private:
	TOptional<FVector> GetSightRayHitLocation() const;
	TOptional<FVector> GetLookDirection() const;
	TOptional<FVector> GetLookVectorHitLocation(const FVector& LookDirection) const;
	TOptional<FVector2D> CrosshairCanvasPosition;

	bool IsCrosshairCreated = false;
};
