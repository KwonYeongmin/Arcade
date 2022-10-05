#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CTimer.generated.h"

UCLASS()
class YM_UNREALPROJ_API ACTimer : public AActor
{
	GENERATED_BODY()
	
public:	
	ACTimer();

protected:
	virtual void BeginPlay() override;

private:
	float timer;
	bool bIsTimerStop = false;
public:
	void StartTimer();// { bIsTimerStop = false; }
	void StopTimer();// { bIsTimerStop = false; }
	void ResetTimer();// { timer = 0; }
	float GetTimer();// { return timer; }
	bool GetTimerStopState();// { return bIsTimerStop; }
	void UpdateTimer();

private:
	int32 countdownTime;
	UPROPERTY(VisibleDefaultsOnly)
		class USceneComponent* Scene;
	UPROPERTY(VisibleDefaultsOnly)
		class UTextRenderComponent* Text;
	FTimerHandle CountdownTimerHandle;

private:
	void UpdateTimerDisplay();
	void AdvanceTimer(); 
	void CountdownHasFinished(); 
	

};
