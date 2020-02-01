// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class ATankPawn;

/**
 * 
 */
UCLASS()
class UDEMY_BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	void BeginPlay() override;
	void Tick(float DeltaSeconds) override;

	ATankPawn* GetControlledTank() const;
	void AimAtCrosshair();
	TOptional< FVector> GetSightRayHitLocation() const;

protected:
	UFUNCTION(BlueprintCallable)
	void SetCrosshairPositionOnCanvas(const FVector2D& position);

	TOptional <FVector2D> m_crosshairCanvasPosition;
};
