#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CArrangeTargets.generated.h"

UCLASS()
class YM_UNREALPROJ_API ACArrangeTargets : public AActor
{
	GENERATED_BODY()
	
public:	
	ACArrangeTargets();

protected:
	virtual void BeginPlay() override;


public:
	UPROPERTY(VisibleDefaultsOnly)
		class USceneComponent* Scene;

private:
	TArray<AActor*> Points;
	FVector PointsLocations[6];

private:
	TSubclassOf<class ACTarget> TargetClass;
	AActor* Targets[6];

public:
	void SpawnTargets();
	void DestroyTargets();
};
