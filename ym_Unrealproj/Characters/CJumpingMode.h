#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CJumpingMode.generated.h"

UCLASS()
class YM_UNREALPROJ_API UCJumpingMode : public UObject
{
	GENERATED_BODY()

public:
	UCJumpingMode();
private:
	class ACharacter*								OwnerCharacter;
	class USpringArmComponent*				SpringArm;
	class UCameraComponent*					Camera;

public:
	UPROPERTY(EditAnywhere)
		FName ToLelvelName ="JumpLevel";

public:
	void OnBegin_Mode(class ACharacter* InCharacter);
	void OnEnd_Mode();
	void OnMode();
	void OnUpdateMode(float DeltaTime);

private:
	int HP;
public:
	int GetHP();
};
