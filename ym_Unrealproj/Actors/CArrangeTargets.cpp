#include "CArrangeTargets.h"
#include "Global.h"
#include "Components/SceneComponent.h"
#include "Actors/CAimActor.h"
#include "Actors/CTarget.h"
// Sets default values
ACArrangeTargets::ACArrangeTargets()
{


	// Scene
	CHelpers::CreateComponent<USceneComponent>(this, &Scene, "Scene");

	// CTargetclass
	CHelpers::GetClass<ACTarget>(&TargetClass,
		"Blueprint'/Game/Actors/BP_CTarget.BP_CTarget_C'");
}

void ACArrangeTargets::BeginPlay()
{
	Super::BeginPlay();

	UGameplayStatics::GetAllActorsWithTag(GetWorld(), "targetSpawnPoints", Points);
	
	for (int i = 0; i < 6; i++) 
	{
		PointsLocations[i] = Points[i]->GetActorLocation();
	}
}



void ACArrangeTargets::SpawnTargets()
{
	ACTarget* targets[6];

	for (int i = 0; i < 6; i++) 
	{
		targets[i] = GetWorld()->SpawnActor<ACTarget>(TargetClass, PointsLocations[i], GetActorRotation());
		Targets[i] = Cast<AActor>(targets[i]);
	}

	for (int i = 0; i < 3; i++) 
	{
		int n = FMath::RandRange(0, 5);
		targets[n]->IsRotationTarget = true;
	}
}

void ACArrangeTargets::DestroyTargets()
{
	for (int i = 0; i < 6; i++) 
	{
		if(Targets[i]) Targets[i]->Destroy();
	}
}

