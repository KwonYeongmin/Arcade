// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CStartLevelActor.generated.h"

UCLASS()
class YM_UNREALPROJ_API ACStartLevelActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ACStartLevelActor();

protected:
	virtual void BeginPlay() override;
private:
	UPROPERTY(VisibleDefaultsOnly)
		TSubclassOf<class UCUserWidget_Menu> MenuUIclass;
	class UCUserWidget_Menu* MenuUI;
};
