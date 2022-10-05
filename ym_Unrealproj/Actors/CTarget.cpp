#include "CTarget.h"

#include "Global.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstanceConstant.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Components/BoxComponent.h"
#include "Components/SceneComponent.h"

#include "Components/TextRenderComponent.h"

#include "Widgets/CUserWidget_Aim.h"

ACTarget::ACTarget()
{
	PrimaryActorTick.bCanEverTick = true;
	
	// 회전
	{
		PitchValue = 0.0f;
		RollValue = 0.0f;
		YawValue = 0.1f;
	}
	

	//mesh
	{
		CHelpers::CreateComponent<USceneComponent>(this, &Scene, "Scene");
		// RootComponent = Scene;

		CHelpers::CreateComponent(this, &BasicMesh, "BasicMesh", RootComponent);
		UStaticMesh* basicMesh;
		CHelpers::GetAsset<UStaticMesh>(&basicMesh, "StaticMesh'/Game/Meshes/Mesh_Sphere.Mesh_Sphere'");
		BasicMesh->SetStaticMesh(basicMesh);
		BasicMesh->SetupAttachment(RootComponent);

		CHelpers::CreateComponent(this, &PillarMesh, "PillarMesh", BasicMesh);
		UStaticMesh* pillarMesh;
		CHelpers::GetAsset<UStaticMesh>(&pillarMesh, "StaticMesh'/Game/Meshes/Mesh_Cube.Mesh_Cube'");
		PillarMesh->SetStaticMesh(pillarMesh);
		PillarMesh->SetupAttachment(BasicMesh);
		
		CHelpers::CreateComponent(this, &Mesh, "Mesh", BasicMesh);
		UStaticMesh* mesh;
		CHelpers::GetAsset<UStaticMesh>(&mesh, "StaticMesh'/Game/Meshes/Mesh_Target_Cylinder.Mesh_Target_Cylinder'");
		Mesh->SetStaticMesh(mesh);
		Mesh->SetupAttachment(BasicMesh);

	}

	//material
	{
		UMaterialInstanceConstant* material1;
		UMaterialInstanceConstant* material2;

		CHelpers::GetAsset<UMaterialInstanceConstant>(&material1, "MaterialInstanceConstant'/Game/UI/Mataerial/MI_TargetBasic_Inst.MI_TargetBasic_Inst'");
		CHelpers::GetAsset<UMaterialInstanceConstant>(&material2, "MaterialInstanceConstant'/Game/UI/Mataerial/MI_AimTarget_Inst.MI_AimTarget_Inst'");
		
		BasicMesh->SetMaterial(0, material1); // mesh에 머테리얼 입히기
		PillarMesh->SetMaterial(0, material1); // mesh에 머테리얼 입히기
		Mesh->SetMaterial(0, material2); // mesh에 머테리얼 입히기
	}	

	BasicMesh->SetRelativeScale3D(FVector(0.2f, 0.2f, 0.2f));
	PillarMesh->SetRelativeScale3D(FVector(0.1f, 0.1f, 1.0f));
	Mesh->SetRelativeScale3D(FVector(1.0f, 1.0f, 0.025f));

}

void ACTarget::BeginPlay()
{
	Super::BeginPlay();

	if (IsRotationTarget) YawValue = 0.1f;
}

void ACTarget::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(IsRotationTarget) Rotate();
	
}

void ACTarget::Rotate()
{
	if (GetActorRotation().Roll > 40 || GetActorRotation().Roll < -40) YawValue *= -1;

	FQuat quatRotation = FQuat(FRotator(PitchValue, RollValue, YawValue));
	AddActorLocalRotation(quatRotation, false, 0, ETeleportType::None);
}

