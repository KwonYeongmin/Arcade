#include "CEventTrigger.h"
#include "Global.h"

#include "Components/BoxComponent.h"
#include "Components/AudioComponent.h"
#include "Components/TextRenderComponent.h"
#include "Components/CGameModeComponent.h"
#include "Particles/ParticleSystem.h"
#include "Sound/SoundBase.h"
#include "Characters/CPlayer.h"
#include "Characters/CShootingMode.h"
#include "GameFramework/Character.h"
#include "Components/SceneComponent.h"

ACEventTrigger::ACEventTrigger()
{
	CHelpers::CreateComponent<USceneComponent>(this, &Scene, "Scene");
	CHelpers::CreateComponent<UBoxComponent>(this, &Box, "Box", Scene);
	CHelpers::CreateComponent<UTextRenderComponent>(this, &Text, "Text", Scene);

//	OwnerCharacter = Cast<ACharacter>(GetOwner());

	

	Box->SetRelativeScale3D(FVector(3));
	Box->bHiddenInGame = false;
	/*
	Text->SetRelativeLocation(FVector(0, 0, 200));
	Text->SetRelativeRotation(FRotator(0, 180, 0));
	Text->SetRelativeScale3D(FVector(2));
	Text->TextRenderColor = FColor::Red;
	Text->HorizontalAlignment = EHorizTextAligment::EHTA_Center;
	*/
	//Text->Text = FText::FromString(GetName());
	
}

void ACEventTrigger::BeginPlay()
{
	Super::BeginPlay();
	
	OnActorBeginOverlap.AddDynamic(this, &ACEventTrigger::ActorBeginOverlap);
	OnActorEndOverlap.AddDynamic(this, &ACEventTrigger::ActorEndOverlap);
	
	/*
	FString str = "Booth";

	switch (Type)
	{
	case ETriggerType::ArcadeBooth:
	{
		str = "ArcadeBooth";
	}break;
	case ETriggerType::ShootingBooth:
	{
		str = "ShootingBooth";
	}break;
	
//	case ETriggerType::JumpingBooth: {str = "JumpingBooth"; } break;

	}*/
	
	//Text->Text = FText::FromString(str);
}

void ACEventTrigger::ActorBeginOverlap(AActor * OverlappedActor, AActor * OtherActor)
{
	ACPlayer* Player = Cast<ACPlayer>(OtherActor);
	if (Type == ETriggerType::GameEnterBooth) return;

	UGameplayStatics::PlaySound2D(this, Sound_In);
	if (Player)
	{
		switch (Type)
		{
			case ETriggerType::ArcadeBooth:
			{
				if(!bExit)Player->OnArcadeMode();
				bExit = true;
			}break;
			case ETriggerType::ShootingBooth:
			{
				if (!bExit)Player->OnShootGameMode();
				bExit = true;
			}break;
			/*
			case ETriggerType::JumpingBooth:
			{
				if (!bExit)	UGameplayStatics::OpenLevel(OtherActor, ToLelvelName);//Player->OnJumpGameMode(); 
				bExit = true;
			}break;*/
		}
	}
}



void ACEventTrigger::ActorEndOverlap(AActor * OverlappedActor, AActor * OtherActor)
{
	bExit = false;
	if(Sound_Out!=NULL)
		UGameplayStatics::PlaySound2D(this, Sound_Out);
}

void ACEventTrigger::SpawnParticle()
{
}


