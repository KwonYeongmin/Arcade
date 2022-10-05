// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CUserWidget_Aim.generated.h"

/**
 * 
 */
UCLASS()
class YM_UNREALPROJ_API UCUserWidget_Aim : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly)
		float MaxTime = 100.0f;
	UPROPERTY(EditDefaultsOnly)
		float Time = 0.1f;
public:
	UFUNCTION(BlueprintCallable)
		void Update(float DeltaTime);
	UFUNCTION(BlueprintCallable)
		void StartTimer();

public:
	void Begin();
	void SetScoreText(int32 score);
public:
	bool TimeOut = false;
	void DecreaseTime();
	int TimeValue;

private:
	FTimerHandle TimerHandle;
	
};
