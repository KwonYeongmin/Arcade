#include "CStartLevelActor.h"

#include "Global.h"
#include "Widgets/CUserWidget_Menu.h"
#include "../CGameInstance.h"

#include "GameFramework/Actor.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Character.h"

ACStartLevelActor::ACStartLevelActor()
{
	CHelpers::GetClass<UCUserWidget_Menu>(&MenuUIclass,
		"WidgetBlueprint'/Game/UI/WB_Menu.WB_Menu_C'");
}

void ACStartLevelActor::BeginPlay()
{
	Super::BeginPlay();
	
	// MenuUI
	{
		MenuUI = CreateWidget<UCUserWidget_Menu>
			(GetWorld(), MenuUIclass);
		MenuUI->AddToViewport();
		MenuUI->SetVisibility(ESlateVisibility::Visible);
		MenuUI->Begin(this);
	}
}

