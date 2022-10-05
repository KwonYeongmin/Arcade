// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/CGameModeComponent.h"	
#include "CEventTrigger.generated.h"

UENUM()
enum class ETriggerType : uint8
{
	GameEnterBooth,
	ArcadeBooth,
	ShootingBooth,
	// JumpingBooth,
	
	Max
};

UCLASS()
class YM_UNREALPROJ_API ACEventTrigger : public AActor
{
	GENERATED_BODY()
	
public:	
	ACEventTrigger();

protected:
	virtual void BeginPlay() override;

private:
	// 
	UPROPERTY(VisibleDefaultsOnly)
		class USceneComponent* Scene;

	UPROPERTY(VisibleDefaultsOnly)
		class UTextRenderComponent* Text;
UPROPERTY(EditDefaultsOnly, Category = "ShootBooth")
		bool bShootingBooth = false;
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Sound")
		class USoundWave* Sound_In;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Sound")
		class USoundWave* Sound_Out;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Particle")
		class UParticleSystem*	Particle;
	UPROPERTY(EditAnywhere, Category = "Type")
		ETriggerType Type;
	UPROPERTY(EditAnywhere)
		FName ToLelvelName;

public:
	FORCEINLINE bool IsShootingBooth() { return bShootingBooth;}
	UPROPERTY(BlueprintReadWrite)
		class UBoxComponent* Box;

private:
	UFUNCTION()
		void ActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);
	UFUNCTION()
		void ActorEndOverlap(AActor* OverlappedActor, AActor* OtherActor);
/*
private:
	UFUNCTION()
		void PlayParticle();

	UFUNCTION()
		void PlayAudio();

	UFUNCTION()
		void StopAudio();
*/
private:
	UPROPERTY(EditAnywhere)
		FString LevelName;
	bool bExit = false;
	void SpawnParticle();
};
