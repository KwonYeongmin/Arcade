// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CParticleSystem.generated.h"

UCLASS()
class YM_UNREALPROJ_API ACParticleSystem : public AActor
{
	GENERATED_BODY()
	
public:	
	ACParticleSystem();
	void Init(FString particlePath, FString soundPath);

public:
	void SpawnParticle(UObject* world, FVector location, FRotator rotator, FVector scale);

private:
	class UParticleSystem* Particle;
	class USoundCue* SoundCue;
};
