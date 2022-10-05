#include "CGameInstance.h"
#include "Global.h"
#include "Characters/CPlayer.h"
#include "GameFramework/Character.h"
#include "Components/CGameModeComponent.h"
#include "Sound/SoundBase.h"
#include "Widgets/CUserWidget_OptionWindow.h"

UCGameInstance::UCGameInstance()
{
	// Mode = CHelpers::GetComponent<UCGameModeComponent>(InOwner);
	DefaultHP = 100;
	DefaultHP = HP;

	// option Window
	optionWidnow = CreateWidget<UCUserWidget_OptionWindow>(this, optionClass);
	// optionWidnow->AddToViewport();
	// optionWidnow->SetVisibility(ESlateVisibility::Hidden);
	
}


void UCGameInstance::AddScore(int index, int value)
{
	Scores[index] += value;
	TotalScore += value;
}

void UCGameInstance::SubtractScore(int index, int value)
{
	Scores[index] = Scores[index] - value >= 0 ? Scores[index] - value : 0;
	TotalScore = TotalScore - value >= 0 ? TotalScore - value : 0;
}

void UCGameInstance::ResetScore(int index)
{
	TotalScore -= Scores[index];
	Scores[index] = 0;

}

void UCGameInstance::ResetTotalScore()
{
	TotalScore = 0;
}

int32 UCGameInstance::GetTotalScore() { return TotalScore; }
int32 UCGameInstance::GetScore(int index) { return Scores[index]; }

void UCGameInstance::AddHP(int32 value)
{
	HP = (HP + value) <= DefaultHP ? (HP + value) : DefaultHP;
}

void UCGameInstance::SubtractHP(int32 value)
{
	HP = (HP - value) > 0 ? (HP - value) : 0;
}

void UCGameInstance::ResetHP()
{
	HP = 0;
}

int32 UCGameInstance::GetCurHP()
{
	return HP;
}
int32 UCGameInstance::GetMaxHP()
{
	return DefaultHP;
}

FString UCGameInstance::GetNickname() 
{
	return Nickname;
}

void UCGameInstance::SetNickname(FString nickname) 
{
	Nickname = nickname;
}

void UCGameInstance::PlaySFXAudio()
{
	UGameplayStatics::CreateSound2D(this, BtnAudio);
}

void UCGameInstance::PlayMusic(AActor* actor,int index) 
{
	UGameplayStatics::CreateSound2D(actor, BGMs[index]);
}


//  Slider로 들어오는 값
// Master볼륨 호출해서 가지고오기
void UCGameInstance::SetVolume(float m, float b, float s) 
{
	//값 셋팅
	MasterVolume = m;
	BGMVolume = b;
	SFXVolume = s;
}

void UCGameInstance::ToggleOptionWindow() 
{

}