// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "COptionComponent.generated.h"


UCLASS( ClassGroup=(GameProject), meta=(BlueprintSpawnableComponent) )
class YM_UNREALPROJ_API UCOptionComponent : public UActorComponent
{
	GENERATED_BODY()

// 마우스 이동
private:
	UPROPERTY(EditDefaultsOnly)
		float HorizontalLookRate = 45;
	UPROPERTY(EditDefaultsOnly)
		float VerticalLookRate = 45;
public:
	FORCEINLINE float GetHorizontalLookRate() { return HorizontalLookRate; }
	FORCEINLINE float GetVerticalLookRate() { return VerticalLookRate; }

public:	
	UCOptionComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
