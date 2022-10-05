#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CTarget.generated.h"

UCLASS()
class YM_UNREALPROJ_API ACTarget : public AActor
{
	GENERATED_BODY()

public:
	ACTarget();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

public:
	// Type -> Enum으로 바꾸기
	UPROPERTY(EditAnywhere, Category = "Type")
		bool IsRotationTarget = false;
	UPROPERTY(EditAnywhere, Category = "Type")
		bool IsMovingTarget = false;
	UPROPERTY(VisibleDefaultsOnly)
		class USceneComponent* Scene;
	UPROPERTY(VisibleDefaultsOnly)
		class UTextRenderComponent* Text;

	// 메쉬
	UPROPERTY(EditAnywhere)
		class UStaticMeshComponent* BasicMesh;
	UPROPERTY(EditAnywhere)
		class UStaticMeshComponent* PillarMesh;
	UPROPERTY(EditAnywhere)
		class UStaticMeshComponent* Mesh;

	// 회전
	UPROPERTY(EditAnywhere, Category = "Movement")
		float PitchValue;
	UPROPERTY(EditAnywhere, Category = "Movement")
		float RollValue;
	UPROPERTY(EditAnywhere, Category = "Movement")
		float YawValue;

private:
	void Rotate();

public:
	UPROPERTY(EditAnywhere, Category = "AimZVaule")
		float ZValue = 0;

	UPROPERTY(EditAnywhere, Category = "AimSize")
		float AimSize = 0;

};
