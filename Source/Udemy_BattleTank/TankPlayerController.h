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

	ATankPawn* GetTankPawn() const;
};
