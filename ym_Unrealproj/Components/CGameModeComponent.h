// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CGameModeComponent.generated.h"

UENUM(BlueprintType)
enum class EGameMode : uint8
{
	Arcade,
	ShootingMode,
	JumpingMode,
	Dead,
	Max,
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGameModeChanged, EGameMode, InPrevMode, EGameMode, InNewMode);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class YM_UNREALPROJ_API UCGameModeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCGameModeComponent();

protected:
	virtual void BeginPlay() override;

private:
	EGameMode Mode;
	
public:
	UPROPERTY(BlueprintAssignable)
		FGameModeChanged OnGameModeChanged;

public:
	void ChangeMode(EGameMode InMode);
private:
	bool bCanMove = true;

public :
	/*
	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsIdleMode() { return Mode == EGameMode::Idle; }*/
	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsArcadeMode() { return Mode == EGameMode::Arcade; }
	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsShootingMode() { return Mode == EGameMode::ShootingMode; } // FullBody
	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsJumpingMode() { return Mode == EGameMode::JumpingMode; } // Collision¸¸ 
	UFUNCTION(BlueprintPure)
		FORCEINLINE bool CanMove() 
	{
		return bCanMove ;
	}

public:
	//void SetIdleMode();
	void SetArcadeMode();
	void SetShootingMode();
	void SetJumpingMode();

//public: 
	//void ChangeGameMode();
};
