// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CAimActor.generated.h"

UCLASS()
class YM_UNREALPROJ_API ACAimActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ACAimActor();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(EditAnywhere)
		class UStaticMeshComponent* Mesh;
	UPROPERTY(VisibleDefaultsOnly)
		class USceneComponent* Scene;
	// 위젯
	UPROPERTY(VisibleDefaultsOnly)
		class UWidgetComponent* AimWidget;
		//class UCUserWidget_Aim* AimWidget;

public:
	UPROPERTY(EditAnywhere) //회전하는 정도
		float Value;
	UPROPERTY(EditAnywhere) //회전하는 빠르기
		float Speed;

private:
	void Shake(float DeltaTime);

public:
	void ToggleAimVisible(bool b);
	UPROPERTY(EditAnywhere, Category = "Movement")
		float YValue;
	UPROPERTY(EditAnywhere, Category = "Movement")
		float ZValue;

private:
	float RunningTime =0.3f;
	float YDirection = 1.0f;
	float ZDirection = 1.0f;
private:
	FVector DefaultLocation;
public:
	bool TimeOut();
public: 
	void SetScoreText(int32 score);
	bool bAimMove = true;
public:
	void StopMove();
private:
	float LerpTimeY;
	float LerpTimeZ;
	FVector GetLocation();
};
