#include "CAimActor.h"

#include "Global.h"

#include "Components/SceneComponent.h"

#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstanceConstant.h"
#include "Materials/MaterialInstanceDynamic.h"

#include "Components/WidgetComponent.h"
#include "Widgets/CUserWidget_Aim.h"


ACAimActor::ACAimActor()
{
	PrimaryActorTick.bCanEverTick = true;

	// 회전
	Speed = 1.0f;
	Value = 1.0f;

	// Scene
	CHelpers::CreateComponent<USceneComponent>(this, &Scene, "Scene");


// Mesh
	CHelpers::CreateComponent(this, &Mesh, "Mesh", RootComponent);
	UStaticMesh* mesh;
	CHelpers::GetAsset<UStaticMesh>(&mesh, "StaticMesh'/Game/Meshes/Mesh_Sphere.Mesh_Sphere'");
	Mesh->SetStaticMesh(mesh);
	Mesh->SetupAttachment(RootComponent);
	Mesh->SetRelativeScale3D( FVector(0.1f, 0.1f, 0.1f));

// material
	UMaterialInstanceConstant* material;
	CHelpers::GetAsset<UMaterialInstanceConstant>(&material, "MaterialInstanceConstant'/Game/UI/Mataerial/MI_TargetBasic_Inst.MI_TargetBasic_Inst'");
	Mesh->SetMaterial(0, material);

	// UI //-> target이 아니라 플레이어
	
	CHelpers::CreateComponent<UWidgetComponent>(this, &AimWidget, "AimWidget", Scene);

	TSubclassOf<UCUserWidget_Aim> aimClass;
	CHelpers::GetClass<UCUserWidget_Aim>(&aimClass, "WidgetBlueprint'/Game/UI/WB_Aim.WB_Aim_C'");

	AimWidget->SetWidgetClass(aimClass);
	AimWidget->SetWidgetSpace(EWidgetSpace::Screen);

	Mesh->SetVisibility(false);
	
}


void ACAimActor::BeginPlay()
{
	Super::BeginPlay();
	
	DefaultLocation = GetActorLocation();

	// 위치
	AimWidget->SetRelativeLocation(FVector(0, 0, 0));
	SetActorHiddenInGame(true);

	bAimMove = true;
	LerpTimeY = 0; LerpTimeZ = 0;
}

// Called every frame
void ACAimActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//if(bAimMove)	Shake(DeltaTime);

	LerpTimeY += DeltaTime*1.1f;
	LerpTimeZ += DeltaTime*1.2f;

	SetActorLocation(GetLocation());
}

void ACAimActor::StopMove() 
{
	bAimMove = false;
}

void ACAimActor::Shake(float DeltaTime)
{
	/*
	{
		FVector newLoc = GetActorLocation();
		float DeltaHeight = (FMath::Sin(RunningTime + DeltaTime) - FMath::Sin(RunningTime));
		newLoc += FVector(GetActorLocation().X, (DeltaHeight)* YValue, (DeltaHeight)* ZValue);
		RunningTime += DeltaTime;
		SetActorLocation(newLoc);
	}
	*/
	//FMath::Lerp( FMath::Sin(LerpTime));

}

FVector ACAimActor::GetLocation()
{
	float Y = FMath::Lerp(DefaultLocation.Y - 10, DefaultLocation.Y + 10, FMath::Sin(LerpTimeY + 1.0f));
	float Z=  FMath::Lerp(DefaultLocation.Z- 10, DefaultLocation.Z + 10, FMath::Sin(LerpTimeZ+ 1.0f));
	FVector loc = FVector(DefaultLocation.X, Y, Z);
	return loc;
}

void ACAimActor::ToggleAimVisible(bool b)
{
	AimWidget->SetVisibility(b);
}

bool ACAimActor::TimeOut()
{
	UCUserWidget_Aim* aimUI = Cast<UCUserWidget_Aim>(AimWidget->GetUserWidgetObject());
	if(aimUI) return aimUI->TimeOut;
	else 	return false;
}


void ACAimActor::SetScoreText(int32 score)
{

	UCUserWidget_Aim* aimUI = Cast<UCUserWidget_Aim>(AimWidget->GetUserWidgetObject());
	aimUI->SetScoreText(score);
	bAimMove = false;
	ToggleAimVisible(true);
	
}