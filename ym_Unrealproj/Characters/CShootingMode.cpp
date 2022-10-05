#include "CShootingMode.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Actor.h"
#include "Kismet/GamePlayStatics.h"
#include "Components/BoxComponent.h"
#include "Sound/SoundCue.h"
#include "Engine/StaticMeshActor.h"
#include "Actors/CTarget.h"
#include "Kismet/GameplayStatics.h"
#include "particles/ParticleSystem.h"
#include "Actors/CAimActor.h"
#include "Actors/CArrangeTargets.h"
#include "CollisionQueryParams.h"
#include "Characters/CPlayer.h"
#include"../CGameInstance.h"

#include "Actors/CParticleSystem.h"

UCShootingMode::UCShootingMode()
{

	CHelpers::GetClass<ACAimActor>(&AimactorClass, "Blueprint'/Game/Actors/BP_CAimActor.BP_CAimActor_C'");
	CHelpers::GetClass<ACArrangeTargets>(&TargetSpawnerClass, "Blueprint'/Game/Actors/BP_CArrangeTargets.BP_CArrangeTargets_C'");

	Particle = NewObject<ACParticleSystem>();
	ACParticleSystem* particle = Cast<ACParticleSystem>(Particle);
	particle->Init("ParticleSystem'/Game/Mobile_Fantasy_FX/ParticleSystems/P_Hit02.P_Hit02'", 
						"SoundCue'/Game/Sounds/sounds/S_RifleShoot_Cue.S_RifleShoot_Cue'");
}

void UCShootingMode::OnBegin_Mode(class ACharacter* InCharacter,AActor* shootingView,AActor* aimView)
{
	OwnerCharacter = InCharacter;
	World = OwnerCharacter->GetWorld();

	//SpringArm
	SpringArm = CHelpers::GetComponent<USpringArmComponent>(OwnerCharacter);

	//Camera
	Camera = CHelpers::GetComponent<UCameraComponent>(OwnerCharacter);
	
	// ViewActor
	ShootingView = shootingView;
	AimView = aimView;

	// Default 값
	DefaultLocation = OwnerCharacter->GetActorLocation();
	DefaultArmLocation = SpringArm->GetRelativeLocation();
	DefaultRotation = OwnerCharacter->GetActorRotation();

		//FVector loc = FVector(ShootingView->GetActorLocation().X, ShootingView->GetActorLocation().Y, ShootingView->GetActorLocation().Z-40);
	 //
	  OwnerCharacter->SetActorLocation(ShootingView->GetActorLocation());
	
	  OnChangeView(ShootingView, OwnerCharacter);
		//OwnerCharacter->SetActorRotation(ShootingView->GetActorRotation());
		//CLog::Print(ShootingView->GetName());
	  //FRotator rot = ShootingView->GetActorRotation() + FRotator(0,10,0);
	//  FString rot_str = "rot: " + FString::SanitizeFloat(rot.Pitch) + " , " + FString::SanitizeFloat(rot.Yaw) + " , "+FString::SanitizeFloat(rot.Roll);
	  OwnerCharacter->SetActorRotation(ShootingView->GetActorRotation());
	  //OwnerCharacter->SetActorRotation(rot);
	
	OnChangeFOV(50.0f);
	SpringArm->TargetArmLength = 200.0f;
	SpringArm->SetRelativeLocation(FVector(DefaultArmLocation.X, DefaultArmLocation.Y, DefaultArmLocation.Z));// +50));
	SpringArm->SetWorldRotation(ShootingView->GetActorRotation());// (0, 0, 0));
	
	//타겟 스포너 생성
	TargetSpawner = World->SpawnActor<ACArrangeTargets>(TargetSpawnerClass,
		OwnerCharacter->GetActorLocation(),OwnerCharacter->GetActorRotation());
	ACArrangeTargets* targetSpawner = Cast<ACArrangeTargets>(TargetSpawner);
	
	//타겟 배치
	SpawnTargets(targetSpawner);
	 
	 //타겟 찾기 및 저장
	FindTarget();

	// 총알 개수
	bulletCount = 5;

	
}

void UCShootingMode::OnEnd_Mode()
{
	{
		SpringArm->TargetArmLength = 300.0f;
		OnChangeFOV(90.0f);
		OwnerCharacter->SetActorLocation(DefaultLocation);
		OwnerCharacter->SetActorRotation(DefaultRotation);
		SpringArm->SetRelativeLocation(DefaultArmLocation);
	}
	
	// 타겟 삭제
	ACArrangeTargets* targetSpawner = Cast<ACArrangeTargets>(TargetSpawner);
	targetSpawner->DestroyTargets();
	 Aim->Destroy();

	 ACPlayer* player = Cast<ACPlayer>(OwnerCharacter);
	 player->EndShootMode();
}

void UCShootingMode::OnMode() 
{
}

void UCShootingMode::OnUpdateMode(float DeltaTime)
{
	
	if (!!Aim) 
	{	
		ACAimActor* aim = Cast<ACAimActor>(Aim);

		if (aim->TimeOut())
		{
			//CLog::Print("TimeOut");
			OnFire();
			OffFire();
		}
	}

	
}




void UCShootingMode::OnAim()
{
	bAim = true;

	// view 변경
	OnChangeView(OwnerCharacter, AimView);
	ACTarget* target = Cast<ACTarget>(Targets[index]);
	TargetCenterLoc = target->Mesh->GetSocketLocation("CenterSocket");
	TargetCenterLoc += FVector(0,0, 10);
	Aim = World->SpawnActor<ACAimActor> (AimactorClass, TargetCenterLoc, Targets[index]->GetActorRotation());
	
	ACAimActor* aim = Cast<ACAimActor>(Aim);
	
	aim->SetActorHiddenInGame(false);
	
}
	

void UCShootingMode::OffAim()
{
	bAim = false;

	// view 변경
	OnChangeView(AimView, OwnerCharacter);

	ACAimActor* aim = Cast<ACAimActor>(Aim);
	aim->SetActorHiddenInGame(true);
	
	aim->ToggleAimVisible(false);
}


void UCShootingMode::OnFire() 
{
	CheckFalse(bAim);
	
	bEndFire = false;

	FVector aimLoc = Aim->GetActorLocation();
	FRotator rot = OwnerCharacter->GetActorRotation();
	
	// 파티클
	ACParticleSystem* particle = Cast<ACParticleSystem>(Particle);
	particle->SpawnParticle(World, aimLoc, rot,FVector(0.2f,0.2f,0.2f));
	
	// 점수 계산
	ACTarget* target = Cast<ACTarget>(Targets[index]);
	TargetCenterLoc = target->Mesh->GetSocketLocation("CenterSocket");
	Distance = abs(powf(TargetCenterLoc.Y - aimLoc.Y,2) + powf(TargetCenterLoc.Z - aimLoc.Z,2));
	JudgeScore(Distance);
	bulletCount--;
}



void UCShootingMode::OffFire()  
{
	CheckFalse(bAim);

	Targets[index]->Destroy();
	Aim->SetLifeSpan(0.8f);

	if (index < TargetNum - 1)
	{
		index++;
		if(bAim) OnAim();
	}
	else 
	{
		ACArrangeTargets* targetSpawner = Cast<ACArrangeTargets>(TargetSpawner);
		SpawnTargets(targetSpawner);
		FindTarget();
	}

	if (bulletCount <= 0)
	{
		if(bAim) OffAim();
		OnEnd_Mode();
	}
}

void UCShootingMode::JudgeScore(float distance)
{ 
	//0~ 220
/*
0~44
44~88
88~132
132~176
176~220
*/

// 파티클 다르게 생성
	int32 score = 0;

	if (distance >= 0 && distance < 44) { score = 50;  bulletCount++; }
	else if (distance >= 44 && distance < 88)  score = 40;
	else if (distance >= 88 && distance < 132)  score = 30;
	else if (distance >= 132 && distance < 176)  score = 20;
	else if (distance >= 176  && distance < 220)  score = 10;
	else  score = 0;

	UCGameInstance* gameInstance = Cast<UCGameInstance>(UGameplayStatics::GetGameInstance(OwnerCharacter->GetWorld()));
	gameInstance->AddScore(0, score);

	ACAimActor* aim = Cast<ACAimActor>(Aim);
	aim->SetScoreText(score);
}

void UCShootingMode::FindTarget()
{
	//타겟 저장 
	TArray<ACTarget*> targets;
	CHelpers::FindActor<ACTarget>(World, targets);
	TargetNum = targets.Num();  //개수 저장
	 
	for (int i = 0; i < TargetNum; i++)  
		Targets[i] = Cast<AActor>(targets[i]);
}


void UCShootingMode::OnChangeView(AActor * OnActor, AActor * InActor) // OnActor: 현재 , InActor: 바뀌게 될
{
	if (InActor)
	{
		APlayerController* playerController = UGameplayStatics::GetPlayerController(OnActor, 0);
		playerController->SetViewTargetWithBlend(InActor, 0.5f);
	}

}

void UCShootingMode::OnChangeFOV(float fov)
{
	Camera->FieldOfView = fov;

}

void UCShootingMode::SpawnTargets(ACArrangeTargets* targetSpawner)
{
	index = 0;
	targetSpawner->SpawnTargets();
}

int32 UCShootingMode::GetBulletCount()
{
	return bulletCount;
}