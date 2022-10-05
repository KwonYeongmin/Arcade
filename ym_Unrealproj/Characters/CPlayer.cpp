#include "CPlayer.h"
#include"Global.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Actor.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/InputComponent.h"
#include "Components/COptionComponent.h"
#include "Components/CGameModeComponent.h"

#include "Characters/CShootingMode.h"
#include "Characters/CJumpingMode.h"

#include "Components/SphereComponent.h"
#include "Widgets/CUserWidget_InGame.h"


#include "Sound/SoundBase.h"
#include"../CGameInstance.h"

#include "Engine/TextureRenderTarget2D.h"
#include "Engine/Texture2D.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Engine/SceneCapture.h"
#include "Materials/MaterialInstanceConstant.h"
#include "Materials/MaterialInstanceDynamic.h"

#include "particles/ParticleSystem.h"
#include "Sound/SoundCue.h"
#include "Actors/CParticleSystem.h"

ACPlayer::ACPlayer()
{
	PrimaryActorTick.bCanEverTick = true;

	 CHelpers::CreateComponent<USpringArmComponent>(this, &SpringArm, "SpringArm", GetMesh());
	 CHelpers::CreateComponent<UCameraComponent>(this, &Camera, "Camera", SpringArm);
	 CHelpers::CreateActorComponent<UCOptionComponent>(this, &Option,"Option");
	 CHelpers::CreateActorComponent<UCGameModeComponent>(this, &Mode, "Mode");
	 CHelpers::CreateComponent<USceneCaptureComponent2D>(this, &SceneCapture, "SceneCapture", SpringArm);
	
	 //CHelpers::CreateActorComponent<USceneCaptureComponent2D>(this, &SceneCapture, "SceneCapture");
	

	 bUseControllerRotationYaw = false;

	 GetMesh()->SetRelativeLocation(FVector(0, 0, -90));
	 GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));

	 // Mesh
	 USkeletalMesh* mesh;
	 CHelpers::GetAsset<USkeletalMesh>(&mesh,
		  "SkeletalMesh'/Game/Character/Mesh/SK_Mannequin.SK_Mannequin'"); 
		 //"Skeleton'/Game/Character/Ch29_nonPBR/character_Skeleton.character_Skeleton'");
		 GetMesh()->SetSkeletalMesh(mesh);
	 
	// Anim
	TSubclassOf<UAnimInstance> animInstance;
	//CHelpers::GetClass<UAnimInstance>(&animInstance, "AnimBlueprint'/Game/Players/ABP_CPlayer.ABP_CPlayer_C'");
	CHelpers::GetClass<UAnimInstance>(&animInstance,"AnimBlueprint'/Game/Players/AnimBP_CPlayer.AnimBP_CPlayer_C'");
	GetMesh()->SetAnimInstanceClass(animInstance);

	// SpringArm
	 SpringArm->TargetArmLength = 200.0f;
	 SpringArm->bDoCollisionTest = false;
	 SpringArm->bUsePawnControlRotation = true;
	 SpringArm->bEnableCameraLag = true;



	 // Move
	 GetCharacterMovement()->RotationRate = FRotator(0, 720, 0);
	 GetCharacterMovement()->bOrientRotationToMovement = true;

	 // Jump
	 JumpHeight = 600.0f; // 아이템에 따라 달라질 수 있음


	 // shootmode
	 ShootMode = NewObject<UCShootingMode>();
	 JumpMode = NewObject<UCJumpingMode>();
	 
	 
	 // UI  
	 CHelpers::GetClass<UCUserWidget_InGame>(&InGameUIclass,
		"WidgetBlueprint'/Game/UI/WB_InGameUI.WB_InGameUI_C'");

	 //sceneCapture
	 Xsize = 1200;
	 Ysize = 1600;
	 SceneCapture->SetupAttachment(GetMesh());
	 RenderTarget2D = NewObject<UTextureRenderTarget2D>();
	 RenderTarget2D->InitAutoFormat(Xsize, Ysize);
	 RenderTarget2D->UpdateResourceImmediate();
	 SceneCapture->CaptureSource = SCS_SceneColorSceneDepth;
	 imgTexture = NULL;
	 //
	 PhotoCount = 0;
}

void ACPlayer::BeginPlay()
{
	Super::BeginPlay();
	
	// Mode->OnGameModeChanged.AddDynamic(this, &ACPlayer::OnGameModeChanged);
	// Mode->ChangeMode(EGameMode::Arcade);
	
	{
		InGameUI = CreateWidget<UCUserWidget_InGame, APlayerController>
			(GetController<APlayerController>(), InGameUIclass);
		InGameUI->AddToViewport();
		InGameUI->SetVisibility(ESlateVisibility::Hidden);
		InGameUI->Begin(this);
	}



	//  level에 따라 mode 바꿔주기
	FString level = UGameplayStatics::GetCurrentLevelName(this, false);

	if (level.Equals("RetroArcade", ESearchCase::CaseSensitive))
	{
		InGameUI->SetVisibility(ESlateVisibility::Visible);
		//MenuUI->SetVisibility(ESlateVisibility::Hidden);
		OnArcadeMode();
	}
	else if (level.Equals("JumpLevel", ESearchCase::CaseSensitive)) 
	{
		InGameUI->SetVisibility(ESlateVisibility::Visible);
		//MenuUI->SetVisibility(ESlateVisibility::Hidden);
		OnJumpGameMode();
	}
	else 
	{
		InGameUI->SetVisibility(ESlateVisibility::Hidden);
		APlayerController* PC = Cast<APlayerController>(GetController());

		if (PC)
		{
			PC->bShowMouseCursor = true;
			PC->bEnableClickEvents = true;
			PC->bEnableMouseOverEvents = true;
		}
	}
	// audio
	/*BGM = BGMs[0];
	UGameplayStatics::PlaySound2D(this, BGM);
	*/
	
	//UI 
	InGameUI->SetNicknameText();

	//
	UCGameInstance* gameInstance = Cast<UCGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	gameInstance->PlayMusic(this,0);
}

void ACPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Mode->IsShootingMode()) 
	{
		ShootMode->OnUpdateMode(DeltaTime);
		UpdateShootModeUI();
	}
	else if (Mode->IsJumpingMode())
	{
		JumpMode->OnUpdateMode(DeltaTime);
		UpdateJumpModeUI();
	}
	else
	{
		 UpdateAracdeModeUI();
	}

	
		
}

void ACPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// 이동
	{
		PlayerInputComponent->BindAxis("MoveForward", this, &ACPlayer::OnMoveForward);
		PlayerInputComponent->BindAxis("MoveRight", this, &ACPlayer::OnMoveRight);
		PlayerInputComponent->BindAxis("HorizontalLook", this, &ACPlayer::OnHorizontalLook);
		//PlayerInputComponent->BindAxis("VerticalLook", this, &ACPlayer::OnVerticalLook);
	}

	// 키입력
	{
	// 점프
		PlayerInputComponent->BindAction("Jump", IE_Pressed,this, &ACPlayer::OnJump);
	// Fire
		PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ACPlayer::OnFire);
		PlayerInputComponent->BindAction("Fire", IE_Released, this, &ACPlayer::OffFire);
		//Aim
		PlayerInputComponent->BindAction("Aim", IE_Pressed, this, &ACPlayer::OnAim);
		PlayerInputComponent->BindAction("Aim", IE_Released, this, &ACPlayer::OffAim);

		//사진
		PlayerInputComponent->BindAction("Picture", IE_Pressed, this, &ACPlayer::OnPhoto);
		PlayerInputComponent->BindAction("Picture", IE_Released, this, &ACPlayer::OffPhoto);
	}
}




void ACPlayer::OnPhoto()
{
	TArray<AActor*> actor;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), "PortraitFrame", actor);

	if (actor[0])
	{
		UStaticMeshComponent* mesh = Cast< UStaticMeshComponent>(actor[0]->GetComponentByClass(UStaticMeshComponent::StaticClass()));

		SceneCapture->TextureTarget = RenderTarget2D;
		SceneCapture->CaptureScene();
		FString name = "Img" + FString::FromInt(PhotoCount);
		imgTexture = SceneCapture->TextureTarget->ConstructTexture2D(this, name, EObjectFlags::RF_NoFlags, CTF_DeferCompression);
	}

	SceneCapture->TextureTarget = RenderTarget2D;
	SceneCapture->UpdateContent();

	UGameplayStatics::PlaySound2D(this, Camera_Sound);
}


void ACPlayer::OffPhoto() 
{
	TArray<AActor*> actor;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), "PortraitFrame", actor);

	if (actor[0])
	{
		UStaticMeshComponent* mesh = Cast< UStaticMeshComponent>(actor[0]->GetComponentByClass(UStaticMeshComponent::StaticClass()));// > ();// > (actor[0]);
		//textrue로 만들기
		UMaterialInstanceDynamic *materialInstance = mesh->CreateDynamicMaterialInstance(0);
		materialInstance->SetTextureParameterValue(FName("ImgTexture"), imgTexture);

	//	InGameUI->TestTexture(imgTexture);
		PhotoCount++;
	}
}


void ACPlayer::OnGameModeChanged(EGameMode InPrevMode,EGameMode InNewMode)
{
	
	switch (InNewMode)
	{
	case EGameMode::Arcade: 
	{
		 OnArcadeMode();
	}  break;
	case EGameMode::ShootingMode: 
	{
		OnShootGameMode();
	}	  break;
	case EGameMode::JumpingMode:			OnJumpGameMode();  break;
	}
}


// ==================  키 입력 ==================
void ACPlayer::OnMoveForward(float InAxis)
{
	
	if (Mode->CanMove()) 
	{
		FRotator rotator = FRotator(0, GetControlRotation().Yaw, 0);
		FVector direction = FQuat(rotator).GetForwardVector();
		AddMovementInput(direction, InAxis);
	}
	
}

void ACPlayer::OnMoveRight(float InAxis)
{

	if (Mode->CanMove()) 
	{
		FRotator rotator = FRotator(0, GetControlRotation().Yaw, 0);
		FVector direction = FQuat(rotator).GetRightVector();
		AddMovementInput(direction, InAxis);
	}
	
}


void ACPlayer::OnHorizontalLook(float InAxis)
{
	float rate = Option->GetHorizontalLookRate();

	if (Mode->CanMove()) 
		AddControllerYawInput(InAxis * rate * GetWorld()->GetDeltaSeconds());
}

void ACPlayer::OnVerticalLook(float InAxis)
{
	float rate = Option->GetVerticalLookRate();
	if (Mode->CanMove()) 
		AddControllerPitchInput(InAxis * rate * GetWorld()->GetDeltaSeconds());
}

void ACPlayer::OnJump()
{
	if (doubleJumpCounter <= 1)  
	{
		ACPlayer::LaunchCharacter(FVector(0, 0, JumpHeight),false, true);
		doubleJumpCounter++;
	}
}

void ACPlayer::Landed(const FHitResult & Hit)
{
	doubleJumpCounter = 0;
}

void ACPlayer::OnSlide()
{
	//CLog::Print("Slide");
}


void ACPlayer::OnAim()
{
	CheckFalse(Mode->IsShootingMode());
	CheckNull(ShootMode);

	 ShootMode->OnAim();
}

void ACPlayer::OffAim()
{
	CheckFalse(Mode->IsShootingMode());
	CheckNull(ShootMode);

	ShootMode->OffAim();
}

void ACPlayer::OnFire()
{

	CheckFalse(Mode->IsShootingMode());

	CheckNull(ShootMode);

	ShootMode->OnFire();

	
}


void ACPlayer::OffFire()
{
	CheckFalse(Mode->IsShootingMode());

	CheckNull(ShootMode);

	
	ShootMode->OffFire();
}

void ACPlayer::OnArcadeMode() 
{
	//UI
	InGameUI->SetArcadeModeUI();

	//Mode
	Mode->SetArcadeMode();
}

void ACPlayer::OnShootGameMode()
{

	//UI
	InGameUI->SetShootModeUI();

	//Mode
	Mode->SetShootingMode();

	//태그로 액터 찾기

	TArray<AActor*> actor1;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), "ShootingView", actor1);
	TArray<AActor*> actor2;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), "AimView", actor2);
	
	if(actor1[0] && actor2[0])
		ShootMode->OnBegin_Mode(Cast<ACharacter>(this), actor1[0],actor2[0]);
}

void ACPlayer::OnJumpGameMode()
{

	JumpMode->OnBegin_Mode(Cast<ACharacter>(this));
	InGameUI->SetJumpModeUI();
	Mode->SetJumpingMode();
}
void ACPlayer ::Test() { CLog::Print("CPLayerTEST"); }

void ACPlayer::EndShootMode()
{
	OnArcadeMode(); 
}

void ACPlayer::EndJumpMode()
{
	OnArcadeMode();
}

void ACPlayer::SpawnActor(AActor* actor , FVector loc, FRotator rot) 
{
	ViewActor =  GetWorld()->SpawnActor<AActor>(ViewActorclass, loc, rot);
}





// 정리 : Tick에서 빼기
void ACPlayer::UpdateShootModeUI() 
{
	// 점수
	UCGameInstance* gameInstance = Cast<UCGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	InGameUI->SetScoreText(gameInstance->GetScore(0));

	//bullet
	InGameUI->SetBulletNumText(ShootMode->GetBulletCount());
}

void ACPlayer::UpdateJumpModeUI() 
{
	// 점수
	UCGameInstance* gameInstance = Cast<UCGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	InGameUI->SetScoreText(gameInstance->GetScore(1));

	//HP
	InGameUI->SetHPText(gameInstance->GetMaxHP(),gameInstance->GetCurHP());
}


void ACPlayer::UpdateAracdeModeUI() 
{
	UCGameInstance* gameInstance = Cast<UCGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	InGameUI->SetScoreText(gameInstance->GetTotalScore());

}


void ACPlayer::TakeDamage(int value) 
{
	UCGameInstance* gameInstance = Cast<UCGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	gameInstance->SubtractHP(value);
}



void ACPlayer::Dead()
{
	/*
	if (Mode->IsJumpingMode())
	{
		//CLog::Print("Dead___");
	
		//if (JumpMode->GetHP() <= 0) //아케이드로 돌아가기
		//	OnArcadeMode();
		//else 
		//{
		//	TArray<AActor*> actors;
		//	UGameplayStatics::GetAllActorsWithTag(GetWorld(), "StartPoint", actors);
		//	FVector point = actors[0]->GetActorLocation();
		//	SetActorLocation(point, false, 0, ETeleportType::None);
		//} // 처음 스폰 장소로 이동하기
		
		

		TArray<AActor*> actors;
		UGameplayStatics::GetAllActorsWithTag(GetWorld(), "StartPoint", actors);
		if (actors[0])
		{
		//	CLog::Print("Actor Location");
			FVector point = actors[0]->GetActorLocation();
			SetActorLocation(point, false, 0, ETeleportType::None);
		}
		else CLog::Print("Actor Not Found");
		 
	}
*/
}

