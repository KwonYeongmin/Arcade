#include "CParticleSystem.h"
#include "Global.h"

#include "particles/ParticleSystem.h"
#include "Sound/SoundCue.h"

ACParticleSystem::ACParticleSystem() 
{
	
}

void ACParticleSystem::Init( FString particlePath, FString soundPath)
{
	CHelpers::GetAsset<UParticleSystem>(&Particle, particlePath);
	CHelpers::GetAsset<USoundCue>(&SoundCue, soundPath);
}




void ACParticleSystem::SpawnParticle(UObject* world, FVector location,FRotator rotator, FVector scale)
{
	UGameplayStatics::SpawnEmitterAtLocation(world,Particle, location, rotator, scale);
	UGameplayStatics::PlaySoundAtLocation(world, SoundCue, location);

}

