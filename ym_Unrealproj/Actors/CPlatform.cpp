#include "CPlatform.h"
#include "Global.h"
#include "Components/SceneComponent.h"
#include "Components/BoxComponent.h"
#include "Characters/CPlayer.h"
#include "Materials/MaterialInstanceConstant.h"
#include "Materials/MaterialInstanceDynamic.h"

ACPlatform::ACPlatform()
{
	PrimaryActorTick.bCanEverTick = true;

	CHelpers::CreateComponent<USceneComponent>(this, &Scene, "Scene");
	RootComponent = Scene;
	CHelpers::CreateComponent<UBoxComponent>(this, &Box, "Box", Scene);

	Box->SetRelativeScale3D(FVector(3));
	Box->bHiddenInGame = false;



}

void ACPlatform::BeginPlay()
{
	Super::BeginPlay();


	CHelpers::CreateComponent(this, &MeshComponent, "MeshComponent", RootComponent);
	MeshComponent->SetStaticMesh(Mesh);
	MeshComponent->SetRelativeScale3D(FVector(1.0f, 1.0f, 1.0f));
	MeshComponent->SetupAttachment(RootComponent);

	OnActorBeginOverlap.AddDynamic(this, &ACPlatform::ActorBeginOverlap);
	OnActorEndOverlap.AddDynamic(this, &ACPlatform::ActorEndOverlap);
}

void ACPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACPlatform::ActorBeginOverlap(AActor * OverlappedActor, AActor * OtherActor)
{
}

void ACPlatform::ActorEndOverlap(AActor * OverlappedActor, AActor * OtherActor)
{
}


