// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CUserWidget_Menu.generated.h"

/**
 * 
 */
UCLASS()
class YM_UNREALPROJ_API UCUserWidget_Menu : public UUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
		void Begin(AActor* actor);


// btn 3개
// editable text -> 닉네임 연결
private:
	UPanelWidget* NicknamePanel;
	UPanelWidget* BtnPanel;
public:
	void ShowNicknamePanel();
	void ShowBtnPanel();
	void HideNicknamePanel();
	void HideBtnPanel();
public:
	UFUNCTION(BlueprintCallable)
		void DownNicknameBtn();
	UFUNCTION(BlueprintCallable)
		void DownStartGameBtn();
	UFUNCTION(BlueprintCallable)
		void DownQuitGameBtn();
	UFUNCTION(BlueprintCallable)
		void DownOptionGameBtn();

private:
	AActor* Actor;
};

//NicknameInput
//InputBtn