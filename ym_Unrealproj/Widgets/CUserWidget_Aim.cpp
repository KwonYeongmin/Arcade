#include "CUserWidget_Aim.h"
#include "Global.h"
#include "Components/Image.h"
#include "Components/PanelWidget.h"
#include "Components/TextBlock.h"

void UCUserWidget_Aim::Begin()
{

//	UPanelWidget* AimPanel = Cast<UPanelWidget>(GetWidgetFromName("AimPanel"));
	UPanelWidget* ScorePanel = Cast<UPanelWidget>(GetWidgetFromName("ScorePanel"));
	ScorePanel->SetVisibility(ESlateVisibility::Hidden);
}

void UCUserWidget_Aim::Update(float DeltaTime)
{	
	UImage* timerImage = Cast<UImage>(GetWidgetFromName("AimTimer")); 
	timerImage->GetDynamicMaterial()->SetVectorParameterValue("Color", FLinearColor::Green);
	timerImage->GetDynamicMaterial()->SetScalarParameterValue("Decimal", TimeValue/MaxTime);

	if (TimeOut) 
	{
		if (TimerHandle.IsValid()) GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
		RemoveFromViewport();
	}
}

void UCUserWidget_Aim::StartTimer()
{
	TimeValue = MaxTime;
	//CLog::Print("StartTimer");
	
	GetWorld()->GetTimerManager().SetTimer(TimerHandle,this,&UCUserWidget_Aim::DecreaseTime,Time,true);
}


void UCUserWidget_Aim::DecreaseTime()
{
	TimeValue--;
	if (TimeValue <= 0) 
	{
		TimeOut = true;
	}
}
void UCUserWidget_Aim::SetScoreText(int32 score) 
{
	UTextBlock* ScoreText = Cast<UTextBlock>(GetWidgetFromName("ScoreText"));
	ScoreText->SetText (FText::FromString(FString::FromInt(score)));
	UPanelWidget* AimPanel = Cast<UPanelWidget>(GetWidgetFromName("AimPanel"));
	UPanelWidget* ScorePanel = Cast<UPanelWidget>(GetWidgetFromName("ScorePanel"));
	ScorePanel->SetVisibility(ESlateVisibility::Visible);
	 AimPanel->SetVisibility(ESlateVisibility::Hidden);
	// CLog::Print(score);
}