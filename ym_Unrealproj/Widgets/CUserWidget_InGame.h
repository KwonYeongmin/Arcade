#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/CGameModeComponent.h"	
#include "CUserWidget_InGame.generated.h"


UCLASS()
class YM_UNREALPROJ_API UCUserWidget_InGame : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void Begin(class ACharacter* InCharacter);
private:
	class ACharacter*	OwnerCharacter;
	/**/
	// 플레이어 모드
	UPROPERTY(VisibleDefaultsOnly)
		class UCGameModeComponent* Mode;
	UPROPERTY(VisibleDefaultsOnly)
		class UCShootingMode* ShootMode;

private:
	// panel
	UPanelWidget* BulletNumUIPanel;
	UPanelWidget* NicknameUIPanel;
	UPanelWidget* ScoreUIPanel;
	UPanelWidget* HPUIPanel;

public:
	void SetBulletNumText(int32 value);
	void SetNicknameText();
	void SetScoreText(int32 Value);
	void LightScoreImage();

	void SetShootModeUI();
	void SetJumpModeUI();
	void SetArcadeModeUI();

	int Score;

public:
	void SetHPText(int32 maxHp, int32 curHp);
	void SetHPBar(int32 maxHp, int32 curHp);
	void TestTexture(UTexture2D* img);

};
