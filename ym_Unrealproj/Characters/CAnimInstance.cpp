// Fill out your copyright notice in the Description page of Project Settings.


#include "CAnimInstance.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

void UCAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
}

void UCAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	ACharacter* character = Cast<ACharacter>(TryGetPawnOwner());
	CheckNull(character); //Null이면 여기서 return

	if (character)
	{
		//  스피드
		Speed = character->GetVelocity().Size2D();

		// 방향
		Direction = CalculateDirection(
			character->GetVelocity(),
			character->GetControlRotation());
		// 공중
		IsInAir = character->GetMovementComponent()->IsFalling();
	}
}
