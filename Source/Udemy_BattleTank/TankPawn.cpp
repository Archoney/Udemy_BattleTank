// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPawn.h"
#include "TankAimingComponent.h"

// Sets default values
ATankPawn::ATankPawn() 
	: m_aimingComponent{ CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component")) }
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ATankPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATankPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ATankPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ATankPawn::AimAt(const FVector& targetLocation)
{
	m_aimingComponent->AimAt(targetLocation);
}

void ATankPawn::SetBarrelReference(UStaticMeshComponent* barrel)
{
	m_aimingComponent->SetBarrelReference(barrel);
}

