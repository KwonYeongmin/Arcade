#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/CGameModeComponent.h"	
#include "CPlayer.generated.h"

UCLASS()
class YM_UNREALPROJ_API ACPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	ACPlayer();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		class USpringArmComponent* SpringArm;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		class UCameraComponent* Camera;
	
private:
	UPROPERTY(EditDefaultsOnly, Category = "BGM")
		class USoundBase*BGMs[3];
	class USoundBase*BGM;
	// 이동
	UPROPERTY(VisibleDefaultsOnly)
		class UCOptionComponent* Option;

	// 플레이어 모드
	UPROPERTY(VisibleDefaultsOnly)
		class UCGameModeComponent* Mode;
	
private:
	UFUNCTION()
		void OnGameModeChanged(EGameMode InPrevMode, EGameMode InNewMode);

	//이동
private:
	void OnMoveForward(float InAxis);
	void OnMoveRight(float InAxis);
	void OnHorizontalLook(float InAxis);
	void OnVerticalLook(float InAxis);
	
	//  점프
	void OnJump();
	virtual void Landed(const FHitResult& Hit) override;
	// 슬라이드
	void OnSlide();

	// 슈팅
private:
	void OnAim();
	void OffAim();
	void OnFire();
	void OffFire();
	void OnPhoto();
	void OffPhoto();
	

	// 점프
private:
	UPROPERTY()
		int doubleJumpCounter = 0;
	UPROPERTY()
		float JumpHeight;

	
public:
		void OnShootGameMode(); // 사격 게임 모드

		void OnArcadeMode();
		void OnJumpGameMode();
	class UCShootingMode* ShootMode;
	class UCJumpingMode* JumpMode;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<AActor> ViewActorclass;
	
	UPROPERTY()
		AActor* ViewActor;
	
private:
	void SpawnActor(AActor* actor, FVector loc, FRotator rot);


	// UI
public:
	
	UPROPERTY(VisibleDefaultsOnly)
		TSubclassOf<class UCUserWidget_InGame> InGameUIclass;

	class UCUserWidget_InGame* InGameUI;


private:
	void UpdateShootModeUI();
	void UpdateJumpModeUI();
	void UpdateAracdeModeUI();
public:
	void EndShootMode();
	void EndJumpMode();
	void Test();
public:
	void Dead();
	void TakeDamage(int value);

private:
		UGameInstance* UGameInstance;


		// take a picture
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Photo")
		USceneCaptureComponent2D *SceneCapture;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Photo")
		UTextureRenderTarget2D* RenderTarget2D;
	UPROPERTY(EditAnywhere, Category = "Photo")
		UMaterial* DefaultMaterial[2];
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Photo")
		class USoundWave* Camera_Sound;
	/*
	UFUNCTION(BlueprintCallable)
		UTextureRenderTarget2D* CreateRenderTarget2D(int32 width, int32 height, bool makeHDR);

	UFUNCTION(BlueprintCallable)
		bool SaveRenderTarget(UTextureRenderTarget2D* renderTarget, FString path, FString fileName);
		*/
	private: 
		int PhotoCount;
		UTexture2D* imgTexture;
		int Xsize;
		int Ysize;


		
};
