#include "CJumpingMode.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"

UCJumpingMode::UCJumpingMode() 
{

}

void UCJumpingMode::OnBegin_Mode(ACharacter * InCharacter)
{
	OwnerCharacter = InCharacter;
	//SpringArm
	SpringArm = CHelpers::GetComponent<USpringArmComponent>(OwnerCharacter);

	//Camera
	Camera = CHelpers::GetComponent<UCameraComponent>(OwnerCharacter);

	// 레벨이동
}

void UCJumpingMode::OnEnd_Mode()
{
}

void UCJumpingMode::OnMode()
{
}

void UCJumpingMode::OnUpdateMode(float DeltaTime)
{
}

int UCJumpingMode::GetHP()
{
	return HP;
}
