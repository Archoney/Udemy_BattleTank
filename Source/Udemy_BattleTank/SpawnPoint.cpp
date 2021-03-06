#include "SpawnPoint.h"

#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

USpawnPoint::USpawnPoint()
{
	PrimaryComponentTick.bCanEverTick = false;
}

AActor* USpawnPoint::GetSpawnedActor() const
{
	return SpawnedActor;
}

void USpawnPoint::BeginPlay()
{
	Super::BeginPlay();

	SpawnedActor =
		GetWorld()->SpawnActorDeferred<AActor>(SpawnClass, GetComponentTransform());
	if (SpawnedActor)
	{
		SpawnedActor->AttachToComponent(
			this, FAttachmentTransformRules::KeepWorldTransform);

		UGameplayStatics::FinishSpawningActor(SpawnedActor, GetComponentTransform());
	}
}