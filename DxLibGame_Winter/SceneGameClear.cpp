#include "SceneGameClear.h"
#include "ScreenFade.h"
#include "ImageObject.h"
#include "Camera.h"	
#include "Input.h"
#include "game.h"
#include "ButtonSystem.h"
#include "ButtonReturnToTitle.h"
#include <cassert>
#include "Statistics.h"

namespace
{
	const std::string kImagePath = "Marine.jpg";
	const std::string kTextPath = "Clear.png";
	const std::string kFontPath = "BroadWay";
	constexpr int kFontSize = 100;
	constexpr int kFontThick = -1;
}

void SceneGameClear::NormalUpdate()
{
	Input& input = Input::GetInstance();

	m_camera->Update();
	m_back->Update();
	m_fade.Update();

#if _DEBUG
	if (input.IsTrigger("ChangeScene_Debug"))
	{
		SceneChangeWithFadeOut("Title");
		return;
	}
#endif
}

void SceneGameClear::ChangeState(State_t nextState)
{

}

void SceneGameClear::AppearGameClearText()
{
}

void SceneGameClear::AppearGetCoinNum()
{
}

void SceneGameClear::AppearKillEnemyNum()
{
}

void SceneGameClear::AppearBreakBlockNum()
{
}

void SceneGameClear::AppearTimeBonusNum()
{
}

void SceneGameClear::AppearScoreNum()
{
}

void SceneGameClear::AppearButton()
{
}

void SceneGameClear::Init()
{
	m_back = std::make_shared<ImageObject>(*m_camera, Vector2::Zero(), kImagePath);
	m_clearText = std::make_shared<ImageObject>(*m_camera, Vector2::Zero(), kTextPath);

	// ボタンの設定
	m_buttonSystem = std::make_shared<ButtonSystem>();
	std::shared_ptr<ButtonReturnToTitle> button = std::make_shared<ButtonReturnToTitle>(Vector2(0,0));
	m_buttonSystem->AddButton(button);
	m_buttonSystem->SetButtonFocus(button);

	// 文字の設定
	m_fontHandle = CreateFontToHandle(kFontPath.c_str(), kFontSize, kFontThick);
	assert(m_fontHandle != -1 && "フォントの読み込みに失敗");
}

void SceneGameClear::Draw() const
{
	m_back->Draw();
	m_clearText->Draw();

	DrawFormatStringToHandle(Game::kScreenHalfWidth, Game::kScreenHalfHeight, 0xffffff, m_fontHandle, "Score:%d", Statistics::GetInstance().Score());

	m_fade.Draw();
}

void SceneGameClear::Entry()
{
	m_fade.Fade(60, 0);
}
