#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Components/TimelineComponent.h"
#include "CShootingMode.generated.h"

//DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FArrange, EGameMode, InNewMode);


UCLASS()
class YM_UNREALPROJ_API UCShootingMode : public UObject
{
	GENERATED_BODY()	

public:
	UCShootingMode();

private:
	class ACharacter*								OwnerCharacter;
	class USpringArmComponent*				SpringArm;
	class UCameraComponent*					Camera;

public:
	void OnBegin_Mode(class ACharacter* InCharacter, AActor* shootingView, AActor* aimView);
	void OnEnd_Mode();
	void OnMode();
	void OnUpdateMode(float DeltaTime);

private:
	UFUNCTION()
		void OnChangeView(AActor* OnActor, AActor* InActor);
	UFUNCTION()
		void OnChangeFOV( float fov);
	
public:
	void OnAim();
	void OffAim();
	void OnFire();
	void OffFire();

private:
	bool bAim = false;
	bool bEndFire = false;

private:
	AActor* ShootingView;
	AActor* AimView;
	UWorld* World;

	TSubclassOf<class ACAimActor> AimactorClass;
	AActor* Aim;
	
	TSubclassOf<class ACArrangeTargets> TargetSpawnerClass;
	AActor* TargetSpawner;
	
	//TSubclassOf<class ACParticleSystem> ParticleClass;
	AActor* Particle;
private: 
	int32 index = 0;

private :
	float Distance = 0;
	void JudgeScore(float distance);
public:
//	int GetScore() { return Score; }
	// ≈∏∞Ÿ
private:
	AActor* Targets[6];
	int TargetNum;

private: 
	void FindTarget();
	void SpawnTargets(ACArrangeTargets* targetSpawner);

private:
	int32 bulletCount = 0;
public :
	int32 GetBulletCount();

	// Ω√¡°
private:
	FVector DefaultLocation;
	FVector DefaultArmLocation;
	FRotator DefaultRotation;

	//
private:
	FVector TargetCenterLoc;
};

