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
	CheckNull(character); //Null�̸� ���⼭ return

	if (character)
	{
		//  ���ǵ�
		Speed = character->GetVelocity().Size2D();

		// ����
		Direction = CalculateDirection(
			character->GetVelocity(),
			character->GetControlRotation());
		// ����
		IsInAir = character->GetMovementComponent()->IsFalling();
	}
}
