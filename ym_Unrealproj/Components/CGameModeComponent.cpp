#include "CGameModeComponent.h"
#include "Global.h"
#include"Characters/Cplayer.h"


UCGameModeComponent::UCGameModeComponent()
{
	// ChangeMode(EGameMode::Arcade);
}


void UCGameModeComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UCGameModeComponent::ChangeMode(EGameMode InMode)
{
	EGameMode mode = Mode;
	Mode = InMode;

	//if (OnGameModeChanged.IsBound())
	//	OnGameModeChanged.Broadcast(mode, InMode);
	
	/*
	FString str = "Prev :";
	FString str2 = "InMode :";
	
	
	
	
	
	if (OnGameModeChanged.IsBound())
	{
		CLog::Print("Bounding");
		OnGameModeChanged.Broadcast(mode, InMode);
		
		if (mode == EGameMode::Arcade) str.Append("Arcade");
		else if (mode == EGameMode::ShootingMode) str.Append("Shoot");
		else if (mode == EGameMode::JumpingMode) str.Append("Jump");

		if (InMode == EGameMode::Arcade) str2.Append("Arcade");
		else if (InMode == EGameMode::ShootingMode) str2.Append("Shoot");
		else if (InMode == EGameMode::JumpingMode) str2.Append("Jump");
	}
	else
	{
		CLog::Print("~Bounding");
	}

	CLog::Print(str);
	CLog::Print(str2);*/

}
		

void UCGameModeComponent::SetArcadeMode()
{
	bCanMove = true;
	ChangeMode(EGameMode::Arcade);

}

void UCGameModeComponent::SetShootingMode()
{
	bCanMove = false;
	ChangeMode(EGameMode::ShootingMode);
	
}

void UCGameModeComponent::SetJumpingMode()
{
	bCanMove = true;
	ChangeMode(EGameMode::JumpingMode);
	
}



