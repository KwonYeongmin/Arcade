#include "CUserWidget_InGame.h"
#include "Global.h"
#include "Components/CGameModeComponent.h"
#include "GameFramework/Character.h"
#include "Components/PanelWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/ProgressBar.h"
#include "../CGameInstance.h"

// test
#include "Engine/Texture2D.h"
void UCUserWidget_InGame::Begin(class ACharacter* InCharacter)
{
	OwnerCharacter = InCharacter;

	// 모드 가져오기
	Mode = CHelpers::GetComponent<UCGameModeComponent>(OwnerCharacter);
	
	//panel 가져오기
	BulletNumUIPanel = Cast<UPanelWidget>(GetWidgetFromName("BulletPanel"));
	NicknameUIPanel = Cast<UPanelWidget>(GetWidgetFromName("NicknamePanel"));
	ScoreUIPanel = Cast<UPanelWidget>(GetWidgetFromName("ScorePanel"));
	HPUIPanel = Cast<UPanelWidget>(GetWidgetFromName("HPPanel"));
	
	BulletNumUIPanel->SetVisibility(ESlateVisibility::Hidden);
	ScoreUIPanel->SetVisibility(ESlateVisibility::Hidden);
	HPUIPanel->SetVisibility(ESlateVisibility::Hidden);

	// text 가져오기
	/*
	BulletNumText = Cast<UTextBlock>(GetWidgetFromName("BulletNumText"));
	NicknameText = Cast<UTextBlock>(GetWidgetFromName("Nickname"));
	ScoreText = Cast<UTextBlock>(GetWidgetFromName("ScoreText"));*/
}



void UCUserWidget_InGame::SetBulletNumText(int32 value)
{
	// OwnerCharacter.shoot
	UTextBlock* BulletNumText = Cast<UTextBlock>(GetWidgetFromName("BulletNumText"));
	BulletNumText->SetText(FText::FromString(FString::FromInt(value)));
}

void UCUserWidget_InGame::SetNicknameText()
{
	UTextBlock* nickname = Cast<UTextBlock>(GetWidgetFromName("Nickname"));

	UCGameInstance* gameInstance = Cast<UCGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	nickname->SetText(FText::FromString(gameInstance->GetNickname()));// ->GetNickname()));
}

void UCUserWidget_InGame::SetScoreText(int32 value)
{
	UTextBlock* ScoreText = Cast<UTextBlock>(GetWidgetFromName("ScoreText"));
	ScoreText->SetText(FText::FromString(FString::FromInt(value)));
}

void UCUserWidget_InGame::SetHPText(int32 maxHp,int32 curHp)
{
	// MaxText
	UTextBlock* maxHpTXT = Cast<UTextBlock>(GetWidgetFromName("HPMaxTXT"));
	maxHpTXT->SetText(FText::FromString(FString::FromInt(maxHp)));

	// CurText
	UTextBlock* curHpTXT = Cast<UTextBlock>(GetWidgetFromName("HPCurTXT"));
	curHpTXT->SetText(FText::FromString(FString::FromInt(curHp)));

	//progressbar
	UProgressBar* hpBar = Cast<UProgressBar>(GetWidgetFromName("HPBar"));
	hpBar->SetPercent((float)curHp /(float)maxHp);
}

void UCUserWidget_InGame::SetHPBar(int32 maxHp,int32 curHp)
{
	//progressbar
	// UTextBlock* ScoreText = Cast<UTextBlock>(GetWidgetFromName("HPBar")); 
}
// 이미지 투명도 조절하기
void UCUserWidget_InGame::LightScoreImage()
{
	UImage* scoreImg = Cast<UImage>(GetWidgetFromName("ScoreImg"));
}



// =============CPlayer에서 선언 ==============
void UCUserWidget_InGame::SetShootModeUI()
{
	// bullet,score
	// hp
	
	{
		BulletNumUIPanel->SetVisibility(ESlateVisibility::Visible);
		ScoreUIPanel->SetVisibility(ESlateVisibility::Visible);
	}
	
	{
		HPUIPanel->SetVisibility(ESlateVisibility::Hidden);
	}
}


void UCUserWidget_InGame::SetJumpModeUI()
{
	// hp,score
	{
		HPUIPanel->SetVisibility(ESlateVisibility::Visible);
		ScoreUIPanel->SetVisibility(ESlateVisibility::Visible);
	}
	// bullet
	{
		BulletNumUIPanel->SetVisibility(ESlateVisibility::Hidden);
	}
	
}

void UCUserWidget_InGame::SetArcadeModeUI()
{
	//
	// bullet, hp, score
	{
		BulletNumUIPanel->SetVisibility(ESlateVisibility::Hidden);
		ScoreUIPanel->SetVisibility(ESlateVisibility::Visible);
		HPUIPanel->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UCUserWidget_InGame::TestTexture(UTexture2D* img)
{
	UImage* scoreImg = Cast<UImage>(GetWidgetFromName("Testimg"));
	scoreImg->SetBrushFromTexture(img);
}
