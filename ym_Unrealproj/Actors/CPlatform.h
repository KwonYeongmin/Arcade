// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CPlatform.generated.h"

UCLASS()
class YM_UNREALPROJ_API ACPlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	ACPlatform();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleDefaultsOnly)
		class USceneComponent* Scene;
	UPROPERTY(VisibleDefaultsOnly)
		class UBoxComponent* Box;
	UPROPERTY(EditDefaultsOnly, Category = "Mesh")
		class UStaticMesh* Mesh;
	class UStaticMeshComponent* MeshComponent;
public:
	UFUNCTION()
		void ActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor) ;
	UFUNCTION()
		void ActorEndOverlap(AActor* OverlappedActor, AActor* OtherActor) ;
};
