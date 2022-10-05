#include "CCoin.h"

#include "Global.h"

#include "Components/StaticMeshComponent.h"

#include "Materials/MaterialInstanceConstant.h"
#include "Materials/MaterialInstanceDynamic.h"

#include "Components/BoxComponent.h"
#include "Components/TextRenderComponent.h"
#include "Components/SceneComponent.h"

ACCoin::ACCoin()
{
	PrimaryActorTick.bCanEverTick = true;

	// È¸Àü
	{
		PitchValue = 0.0f;
		RollValue = 2.0f;
		YawValue = 0.0f;
	}

	CHelpers::CreateComponent<USceneComponent>(this, &Scene, "Scene");
	CHelpers::CreateComponent<UBoxComponent>(this, &Box, "Box", Scene);
	CHelpers::CreateComponent<UTextRenderComponent>(this, &Text, "Text", Scene);
	
	RootComponent = Scene;

	// : Mesh
	CHelpers::CreateComponent(this, &Mesh, "Mesh", RootComponent);
	UStaticMesh* mesh;
	CHelpers::GetAsset<UStaticMesh>(&mesh, "StaticMesh'/Game/LowPolyCubeWorld/Meshes/Gold/Mesh_Gold_Coin_01.Mesh_Gold_Coin_01'");
	Mesh->SetStaticMesh(mesh);
	//
	/*
	UMaterialInstanceConstant* material;
	CHelpers::GetAsset<UMaterialInstanceConstant>(&material, "Material'/Game/Mateiral/MI_Coin.MI_Coin'");
	Mesh->SetMaterial(0, material);
	*/
	Mesh->SetRelativeScale3D(FVector(5.0f, 5.0f, 5.0f));
	
	Mesh->SetupAttachment(RootComponent);
}

void ACCoin::BeginPlay()
{
	Super::BeginPlay();
	//
	Mesh->SetRelativeRotation(FRotator(0, -90, 0));
}

void ACCoin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

// 	Text->SetText(FString::FromInt((int32)RollValue));

	Rotate();
}

void ACCoin::Rotate()
{
	FQuat quatRotation = FQuat(FRotator(PitchValue, RollValue, YawValue));
	AddActorLocalRotation(quatRotation, false, 0, ETeleportType::None);
}

void ACCoin::ActorBeginOverlap(AActor * OverlappedActor, AActor * OtherActor)
{
}

void ACCoin::ActorEndOverlap(AActor * OverlappedActor, AActor * OtherActor)
{
}

