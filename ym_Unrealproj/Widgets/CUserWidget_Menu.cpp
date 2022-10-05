#include "CUserWidget_Menu.h"

#include "Global.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "GameFramework/Character.h"
#include "Components/PanelWidget.h"
#include "../CGameInstance.h"
#include "Components/EditableTextBox.h"


void UCUserWidget_Menu::Begin(AActor* actor) 
{
	Actor = actor;
	NicknamePanel = Cast<UPanelWidget>(GetWidgetFromName("NicknamePanel"));
	BtnPanel = Cast<UPanelWidget>(GetWidgetFromName("BtnPanel")); 

	ShowNicknamePanel();
}


void UCUserWidget_Menu::DownNicknameBtn()
{
	UEditableTextBox* nickname = Cast<UEditableTextBox>(GetWidgetFromName("NicknameInput"));
	
	UCGameInstance* gameInstance = Cast<UCGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	gameInstance->SetNickname(nickname->GetText().ToString());
	gameInstance->PlaySFXAudio();
	ShowBtnPanel();

	
}

void UCUserWidget_Menu::DownStartGameBtn()
{
	FName level = "RetroArcade";
	UGameplayStatics::OpenLevel(this, level);

	UCGameInstance* gameInstance = Cast<UCGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	gameInstance->PlaySFXAudio();
}

void UCUserWidget_Menu::DownQuitGameBtn() 
{
	// QuitGame();
	APlayerController* SpecificPlayer = GetWorld()->GetFirstPlayerController();
	UKismetSystemLibrary::QuitGame(Actor->GetWorld(), SpecificPlayer, EQuitPreference::Quit, true);
	UCGameInstance* gameInstance = Cast<UCGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	gameInstance->PlaySFXAudio();
}

void UCUserWidget_Menu::DownOptionGameBtn() 
{


}

void UCUserWidget_Menu::ShowNicknamePanel()
{
	NicknamePanel->SetVisibility(ESlateVisibility::Visible);
	BtnPanel->SetVisibility(ESlateVisibility::Hidden);
}

void UCUserWidget_Menu::ShowBtnPanel()
{
	NicknamePanel->SetVisibility(ESlateVisibility::Hidden);
	BtnPanel->SetVisibility(ESlateVisibility::Visible);
}

void UCUserWidget_Menu::HideNicknamePanel()
{

}

void UCUserWidget_Menu::HideBtnPanel()
{

}