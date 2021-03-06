#pragma once

#include "Components/SceneComponent.h"
#include "CoreMinimal.h"

#include "SpawnPoint.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class UDEMY_BATTLETANK_API USpawnPoint : public USceneComponent
{
	GENERATED_BODY()

public:
	USpawnPoint();
	AActor* GetSpawnedActor() const;

protected:
	void BeginPlay() override;

	UPROPERTY(BlueprintReadWrite, Category = "Setup")
	TSubclassOf<AActor> SpawnClass;

private:
	AActor* SpawnedActor{nullptr};
};
