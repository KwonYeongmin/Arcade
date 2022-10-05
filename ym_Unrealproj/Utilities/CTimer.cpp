#include "CTimer.h"

#include "Global.h"
#include "TimerManager.h"
#include "Components/TextRenderComponent.h"

ACTimer::ACTimer()
{
 	
	PrimaryActorTick.bCanEverTick = true;

	CHelpers::CreateComponent<USceneComponent>(this, &Scene, "Scene");
	CHelpers::CreateComponent<UTextRenderComponent>(this, &Text, "Text", Scene);

	Text->SetRelativeLocation(FVector(0, 0, 100));
	Text->SetRelativeRotation(FRotator(0, 180, 0));
	Text->SetRelativeScale3D(FVector(2));
	Text->TextRenderColor = FColor::Red;
	Text->HorizontalAlignment = EHorizTextAligment::EHTA_Center;
	Text->Text = FText::FromString(GetName());

	countdownTime = 5.0f;
	
	
	// GetWorldTimerManager().SetTimer(CountdownTimerHandle, this, &ACTimer::AdvanceTimer, 1.0f, true, 2.0f);
	
}

void ACTimer::BeginPlay()
{
	Super::BeginPlay();

	UpdateTimerDisplay();
	GetWorldTimerManager().SetTimer(CountdownTimerHandle, this, &ACTimer::AdvanceTimer, 1.0f, true);
}


void ACTimer::StartTimer()
{
}

void ACTimer::StopTimer()
{
}

void ACTimer::ResetTimer()
{
}

float ACTimer::GetTimer()
{
	return 0.0f;
}

bool ACTimer::GetTimerStopState()
{
	return false;
}

void ACTimer::UpdateTimer()
{
	/*
	if (bIsTimerStop) return;
	timer += Time.deltaTime;
	FTime*/
}

void ACTimer::UpdateTimerDisplay()
{
	//Text->SetText(FString::FromInt(FMath::Max(countdownTime, 0)));
	//Text->SetText( FString::FromInt((int32)countdownTime));
}

void ACTimer::AdvanceTimer()
{
	--countdownTime; 
	UpdateTimerDisplay();
	if (countdownTime < 1)
	{
		// 카운트다운이 완료되면 타이머를 중지 
		GetWorldTimerManager().ClearTimer(CountdownTimerHandle); 
		CountdownHasFinished(); 
	}
}

void ACTimer::CountdownHasFinished()
{
	//Text->SetText(TEXT("Go!"));
}



