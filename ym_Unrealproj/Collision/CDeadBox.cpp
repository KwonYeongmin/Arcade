#include "CDeadBox.h"
#include "Global.h"
#include "Characters/CPlayer.h"
#include "Components/CGameModeComponent.h"
#include "Components/BoxComponent.h"
#include "Components/TextRenderComponent.h"
#include "GameFramework/Character.h"
#include "Components/SceneComponent.h"
ACDeadBox::ACDeadBox()
{
 	
	PrimaryActorTick.bCanEverTick = true;
	CHelpers::CreateComponent<USceneComponent>(this, &Scene, "Scene");
	CHelpers::CreateComponent<UBoxComponent>(this, &Box, "Box", Scene);
	CHelpers::CreateComponent<UTextRenderComponent>(this, &Text, "Text", Scene);
	Box->SetRelativeScale3D(FVector(3));
	Box->bHiddenInGame = false;
}


void ACDeadBox::BeginPlay()
{
	Super::BeginPlay();

	OnActorBeginOverlap.AddDynamic(this, &ACDeadBox::ActorBeginOverlap);
	OnActorEndOverlap.AddDynamic(this, &ACDeadBox::ActorEndOverlap);
}


void ACDeadBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACDeadBox::ActorBeginOverlap(AActor * OverlappedActor, AActor * OtherActor)
{
	ACPlayer* Player = Cast<ACPlayer>(OtherActor);

	if (Player) 
		Player->TakeDamage(Damage);
}

void ACDeadBox::ActorEndOverlap(AActor * OverlappedActor, AActor * OtherActor)
{
}

