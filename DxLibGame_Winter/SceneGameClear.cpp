#include "ButtonReturnToTitleFromClearScene.h"
#include "ButtonSystem.h"
#include "Camera.h"	
#include "game.h"
#include "ImageObject.h"
#include "Input.h"
#include "SceneGameClear.h"
#include "ScreenFade.h"
#include "Statistics.h"
#include <cassert>

namespace
{
	const std::string kImagePath = "Marine.jpg";
	const std::string kTextPath  = "Clear.png";
	const std::string kFontPath  = "Data/Font/07にくまるフォント.otf";
	const std::string kFontName  = "07にくまるフォント";
	// フォーマットが取って置けることに初めて気づく
	const std::string kCoinText  = "ゲットしたコインの数：%02dｘ%d　= スコア：%d";
	const std::string kEnemyText = "倒した敵の数　　　　：%02dｘ%d　= スコア：%d";
	const std::string kBlockText = "壊したブロックの数　：%02dｘ%d　= スコア：%d";
	const std::string kTimeText  = "クリアタイム　　　　：%02d：%02d　= 倍率：x%d";
	const std::string kTotalText  = "総スコア：%d";
	constexpr int kFontSize = 40;
	constexpr int kTotalScoreSize = 80;
	constexpr int kFontThick = -1;
	constexpr int kTextShadowOffset = 2;
	const Vector2 kClearTextPos       = { 0, -320 };
	const Vector2 kTextShiftOffset    = { 0, 50 };
	const Vector2 kCoinScoreInitPos   = { 2000, 300 };
	const Vector2 kEnemyScoreInitPos  = kCoinScoreInitPos + kTextShiftOffset;
	const Vector2 kBlockScoreInitPos  = kEnemyScoreInitPos + kTextShiftOffset;
	const Vector2 kTimeScoreInitPos   = kBlockScoreInitPos + kTextShiftOffset;
	const Vector2 kTotalScoreInitPos  = kTimeScoreInitPos + Vector2(0,100);
	const Vector2 kCoinTextTargetPos  = { 100.0f, kCoinScoreInitPos.y };
	const Vector2 kEnemyTextTargetPos = { 100.0f, kEnemyScoreInitPos.y };
	const Vector2 kBlockTextTargetPos = { 100.0f, kBlockScoreInitPos.y };
	const Vector2 kTimeTextTargetPos  = { 100.0f, kTimeScoreInitPos.y };
	const Vector2 kTotalTextTargetPos = { 100.0f, kTotalScoreInitPos.y };
	const Vector2 kClearTextMoveSpeed = { 0, 2 };
	constexpr int kClearTextAppearFrame = 60;
	constexpr int kScoreAppearFrame = 90;
	const Vector2 kButtonPos = { 1000, 600 };
}

void SceneGameClear::NormalUpdate()
{
	m_camera->Update();
	m_back->Update();
	(this->*m_state)();
	m_fade.Update();
	++m_stateFrameCount;
}

void SceneGameClear::ChangeState(State_t nextState)
{
	m_state = nextState;
	m_stateFrameCount = 0;
}

void SceneGameClear::Skip()
{
	m_clearText->Tere({ 0, -200 });
	m_coinScoreText->pos = kCoinTextTargetPos;
	m_lerpCoinScore = Statistics::GetInstance().ScoreCoin();
	m_enemyScoreText->pos = kEnemyTextTargetPos;
	m_lerpEnemyScore = Statistics::GetInstance().ScoreEnemy();
	m_blockScoreText->pos = kBlockTextTargetPos;
	m_lerpBlockScore = Statistics::GetInstance().ScoreBlock();
	m_totalScoreText->pos = kTotalTextTargetPos;
	m_lerpTimeScore = Statistics::GetInstance().ScoreTime();
	m_button->ChangeTransparency(255);
	ChangeState(&SceneGameClear::NormalState);
}

void SceneGameClear::AppearGameClearText()
{
	m_clearText->Move(kClearTextMoveSpeed);
	if (m_stateFrameCount > kClearTextAppearFrame)
	{
		ChangeState(&SceneGameClear::AppearGetCoinNum);
		return;
	}
	if (Input::GetInstance().IsTrigger("Submit"))
	{
		// スキップ
		Skip();
		return;
	}
}

void SceneGameClear::AppearGetCoinNum()
{
	// 左にずらして現れる感じ
	m_coinScoreText->pos.x = std::lerp(m_coinScoreText->pos.x, kCoinTextTargetPos.x, 0.1f);
	// 値をlerpで表示する
	m_lerpCoinScore = std::lerp(m_lerpCoinScore, static_cast<float>(Statistics::GetInstance().ScoreCoin()), 0.05f);
	if (m_stateFrameCount > kScoreAppearFrame)
	{
		// キャッシュしたほうがメモリ効率はいいがメンバが増える
		m_lerpCoinScore = Statistics::GetInstance().ScoreCoin();
		ChangeState(&SceneGameClear::AppearKillEnemyNum);
		return;
	}
	if (Input::GetInstance().IsTrigger("Submit"))
	{
		Skip();
		return;
	}
}

void SceneGameClear::AppearKillEnemyNum()
{
	m_enemyScoreText->pos.x = std::lerp(m_enemyScoreText->pos.x, kEnemyTextTargetPos.x, 0.1f);
	// 値をlerpで表示する
	m_lerpEnemyScore = std::lerp(m_lerpEnemyScore, static_cast<float>(Statistics::GetInstance().ScoreEnemy()), 0.05f);
	if (m_stateFrameCount > kScoreAppearFrame)
	{
		m_lerpEnemyScore = Statistics::GetInstance().ScoreEnemy();
		ChangeState(&SceneGameClear::AppearBreakBlockNum);
		return;
	}
	if (Input::GetInstance().IsTrigger("Submit"))
	{
		Skip();
		return;
	}
}

void SceneGameClear::AppearBreakBlockNum()
{
	m_blockScoreText->pos.x = std::lerp(m_blockScoreText->pos.x, kBlockTextTargetPos.x, 0.1f);
	m_lerpBlockScore = std::lerp(m_lerpBlockScore, static_cast<float>(Statistics::GetInstance().ScoreBlock()), 0.05f);
	if (m_stateFrameCount > kScoreAppearFrame)
	{
		m_lerpBlockScore = Statistics::GetInstance().ScoreBlock();
		ChangeState(&SceneGameClear::AppearTimeBonusNum);
		return;
	}
	if (Input::GetInstance().IsTrigger("Submit"))
	{
		Skip();
		return;
	}
}

void SceneGameClear::AppearTimeBonusNum()
{
	m_timeScoreText->pos.x = std::lerp(m_timeScoreText->pos.x, kTimeTextTargetPos.x, 0.1f);
	m_lerpTimeScore = std::lerp(m_lerpTimeScore, static_cast<float>(Statistics::GetInstance().ScoreTime()), 0.05f);
	if (m_stateFrameCount > kScoreAppearFrame)
	{
		m_lerpTimeScore = Statistics::GetInstance().ScoreTime();
		ChangeState(&SceneGameClear::AppearScoreNum);
		return;
	}
	if (Input::GetInstance().IsTrigger("Submit"))
	{
		Skip();
		return;
	}
}

void SceneGameClear::AppearScoreNum()
{
	m_totalScoreText->pos.x = std::lerp(m_totalScoreText->pos.x, kTotalTextTargetPos.x, 0.1f);
	m_lerpTotalScore = std::lerp(m_lerpTotalScore, static_cast<float>(Statistics::GetInstance().ScoreTotal()), 0.05f);
	if (m_stateFrameCount > kScoreAppearFrame)
	{
		m_lerpTotalScore = Statistics::GetInstance().ScoreTotal();
		ChangeState(&SceneGameClear::AppearButton);
		return;
	}
	if (Input::GetInstance().IsTrigger("Submit"))
	{
		Skip();
		return;
	}
}

void SceneGameClear::AppearButton()
{
	// kScoreAppearFrameで透明度が255になってほしい
	int param = static_cast<int>(255.0f / kScoreAppearFrame * m_stateFrameCount);
	m_button->ChangeTransparency(param);
	if (m_stateFrameCount > kScoreAppearFrame)
	{
		ChangeState(&SceneGameClear::NormalState);
		return;
	}
	if (Input::GetInstance().IsTrigger("Submit"))
	{
		Skip();
		return;
	}
}

void SceneGameClear::NormalState()
{
	m_buttonSystem->Update();
}

SceneGameClear::~SceneGameClear()
{
	// フォントの削除
	DeleteFontToHandle(m_totalScoreText->fontHandle);
	DeleteFontToHandle(m_font);
	RemoveFontResourceExA("", FR_PRIVATE, NULL);
}

void SceneGameClear::Init()
{
	m_back = std::make_shared<ImageObject>(*m_camera, Vector2::Zero(), kImagePath);
	m_clearText = std::make_shared<ImageObject>(*m_camera, kClearTextPos, kTextPath);

	// ボタンの設定
	m_buttonSystem = std::make_shared<ButtonSystem>();
	m_button = std::make_shared<ButtonReturnToTitleFromClearScene>(kButtonPos);
	m_button->ChangeTransparency(0);
	m_buttonSystem->AddButton(m_button);
	m_buttonSystem->SetButtonFocus(m_button);

	AddFontResourceExA(kFontPath.c_str(), FR_PRIVATE, NULL);

	// 文字の設定
	m_font = CreateFontToHandle(kFontName.c_str(), kFontSize, kFontThick);
	assert(m_font != -1 && "フォントの読み込みに失敗");
	int totalScoreFont = CreateFontToHandle(kFontName.c_str(), kTotalScoreSize, kFontThick);
	assert(totalScoreFont != -1 && "フォントの読み込みに失敗");

	m_coinScoreText = std::make_shared<Text>(kCoinScoreInitPos, kCoinText, m_font);
	m_enemyScoreText = std::make_shared<Text>(kEnemyScoreInitPos, kEnemyText, m_font);
	m_blockScoreText = std::make_shared<Text>(kBlockScoreInitPos, kBlockText, m_font);
	m_timeScoreText = std::make_shared<Text>(kTimeScoreInitPos, kTimeText, m_font);
	m_totalScoreText = std::make_shared<Text>(kTotalScoreInitPos, kTotalText, totalScoreFont);

	ChangeState(&SceneGameClear::AppearGameClearText);
}

void SceneGameClear::Draw() const
{
	m_back->Draw();
	m_clearText->Draw();
	m_buttonSystem->Draw();

	Statistics& stats = Statistics::GetInstance();

	// 縁を描画しているので二倍書いてます
	// クラス化しろ定期
	DrawFormatStringToHandle(static_cast<int>(m_coinScoreText->pos.x + kTextShadowOffset),
		static_cast<int>(m_coinScoreText->pos.y + kTextShadowOffset), 0x000000, m_coinScoreText->fontHandle, m_coinScoreText->text.c_str(), stats.GetCoinNum(), stats.GetCoinScoreMult(), static_cast<int>(m_lerpCoinScore));
	DrawFormatStringToHandle(static_cast<int>(m_coinScoreText->pos.x),
		static_cast<int>(m_coinScoreText->pos.y), 0xffffff, m_coinScoreText->fontHandle, m_coinScoreText->text.c_str(), stats.GetCoinNum(), stats.GetCoinScoreMult(), static_cast<int>(m_lerpCoinScore));

	DrawFormatStringToHandle(static_cast<int>(m_enemyScoreText->pos.x + kTextShadowOffset),
		static_cast<int>(m_enemyScoreText->pos.y + kTextShadowOffset), 0x000000, m_enemyScoreText->fontHandle, m_enemyScoreText->text.c_str(), stats.KilledEnemyNum(), stats.GetEnemyScoreMult(), static_cast<int>(m_lerpEnemyScore));
	DrawFormatStringToHandle(static_cast<int>(m_enemyScoreText->pos.x),
		static_cast<int>(m_enemyScoreText->pos.y), 0xffffff, m_enemyScoreText->fontHandle, m_enemyScoreText->text.c_str(), stats.KilledEnemyNum(), stats.GetEnemyScoreMult(), static_cast<int>(m_lerpEnemyScore));

	DrawFormatStringToHandle(static_cast<int>(m_blockScoreText->pos.x + kTextShadowOffset),
		static_cast<int>(m_blockScoreText->pos.y + kTextShadowOffset), 0x000000, m_blockScoreText->fontHandle, m_blockScoreText->text.c_str(), stats.BreakBlockNum(), stats.GetBlockScoreMult(), static_cast<int>(m_lerpBlockScore));
	DrawFormatStringToHandle(static_cast<int>(m_blockScoreText->pos.x),
		static_cast<int>(m_blockScoreText->pos.y), 0xffffff, m_blockScoreText->fontHandle, m_blockScoreText->text.c_str(), stats.BreakBlockNum(), stats.GetBlockScoreMult(), static_cast<int>(m_lerpBlockScore));

	DrawFormatStringToHandle(static_cast<int>(m_timeScoreText->pos.x + kTextShadowOffset),
		static_cast<int>(m_timeScoreText->pos.y + kTextShadowOffset), 0x000000, m_timeScoreText->fontHandle, m_timeScoreText->text.c_str(), stats.ClearTimeMinutes(), stats.ClearTimeSeconds(), static_cast<int>(m_lerpTimeScore));
	DrawFormatStringToHandle(static_cast<int>(m_timeScoreText->pos.x),
		static_cast<int>(m_timeScoreText->pos.y), 0xffffff, m_timeScoreText->fontHandle, m_timeScoreText->text.c_str(), stats.ClearTimeMinutes(), stats.ClearTimeSeconds(), static_cast<int>(m_lerpTimeScore));

	DrawFormatStringToHandle(static_cast<int>(m_totalScoreText->pos.x + kTextShadowOffset),
		static_cast<int>(m_totalScoreText->pos.y + kTextShadowOffset), 0x000000, m_totalScoreText->fontHandle, m_totalScoreText->text.c_str(), static_cast<int>(m_lerpTotalScore));
	DrawFormatStringToHandle(static_cast<int>(m_totalScoreText->pos.x),
		static_cast<int>(m_totalScoreText->pos.y), 0xffffff, m_totalScoreText->fontHandle, m_totalScoreText->text.c_str(), static_cast<int>(m_lerpTotalScore));

	m_fade.Draw();
}

void SceneGameClear::Entry()
{
	m_fade.Fade(60, 0);
}

void SceneGameClear::ReturnToTitle()
{
	SceneChangeWithFadeOut("Title");
}
