// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "CGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class YM_UNREALPROJ_API UCGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UCGameInstance();

	// ============= Score ===============

private:
	UPROPERTY()
		int32 Scores[2];
	UPROPERTY()
		int32 TotalScore;


public:
	void AddScore(int index, int value);
	void SubtractScore(int index, int vaule);
	void ResetScore(int index);
	void ResetTotalScore();

public:
	int32 GetTotalScore();
	int32 GetScore(int index);

	// ============= HP ===============
private:
	UPROPERTY()
		int32 HP;
	UPROPERTY()
		int32 DefaultHP = 100 ;
public:
	void AddHP(int32 value);
	void SubtractHP(int32 value);
	void ResetHP();
	int32 GetCurHP();
	int32 GetMaxHP();

	// ========== nickname ==============
private:
	FString Nickname;

	
public:
	FString GetNickname();
	void SetNickname(FString nickname);


	// ======== sound =============
private:

	UPROPERTY(EditDefaultsOnly, Category = "BGM")
		class USoundBase*BGMs[3];
	UPROPERTY(EditDefaultsOnly, Category = "SFX")
		class USoundBase* BtnAudio;

public:
	void PlayMusic(AActor* actor,int index);
	void PlaySFXAudio();
	// ============= Window
public:
	/*
	float MasterVolume;
	float BGMVolume;
	float SFXVolume;
`	*/
	void SetVolume(float m, float b, float s);
	void ToggleOptionWindow();

	UPROPERTY(VisibleDefaultsOnly)
		TSubclassOf<class UCUserWidget_OptionWindow> optionClass;
	class UCUserWidget_OptionWindow* optionWidnow;
private:
	bool bVisible;// = false;
};
