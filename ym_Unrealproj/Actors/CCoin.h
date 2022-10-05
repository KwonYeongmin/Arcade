// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CCoin.generated.h"

UCLASS()
class YM_UNREALPROJ_API ACCoin : public AActor
{
	GENERATED_BODY()
	
public:	
	ACCoin();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override; //ȸ�� �ϵ���

public: 	
	UPROPERTY(VisibleDefaultsOnly)
		class USceneComponent* Scene;

	UPROPERTY(VisibleDefaultsOnly)
		class UTextRenderComponent* Text;

	UPROPERTY(VisibleDefaultsOnly)
		class UBoxComponent* Box;

	UPROPERTY(VisibleDefaultsOnly)
		class UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, Category = "Movement")
		float PitchValue;
	UPROPERTY(EditAnywhere, Category = "Movement")
		float RollValue;
	UPROPERTY(EditAnywhere, Category = "Movement")
		float YawValue;

private:
	void Rotate();

private: 
	// �Լ�
	// ���ھ� Ŭ���� (�ε��� Ŭ�������� ������ ����)
	
private:
	UFUNCTION()
		void ActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor); // �ε����� ������� , ���� ȹ��
	UFUNCTION()
		void ActorEndOverlap(AActor* OverlappedActor, AActor* OtherActor); 

};
