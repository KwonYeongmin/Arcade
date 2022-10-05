// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/AudioComponent.h"
#include "CAudioComponent.generated.h"


UCLASS()
class YM_UNREALPROJ_API UCAudioComponent : public UAudioComponent
{
	GENERATED_BODY()
	
public:
	UCAudioComponent();
private:
	class USoundBase* FootstepSound;
	class USoundBase* BGMSound[3];

protected:
	virtual void BeginPlay() override;

};
