#include "ButtonReturnToTitle.h"
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
	const std::string kTextPath = "Clear.png";
	const std::string kFontPath = "Data/Font/memoir.otf";
	const std::string kFontName = "�߂���[��";
	const std::string kCoinText = "�Q�b�g�����R�C���̐��F%d";
	const std::string kEnemyText = "�|�����G�̐��F%d";
	const std::string kBlockText = "�󂵂��u���b�N�̐��F%d";
	constexpr int kFontSize = 100;
	constexpr int kFontThick = -1;
	const Vector2 kClearTextPos = { 0, -200 };
	const Vector2 kTextShiftOffset = { 100, 0 };
	const Vector2 kCoinScoreInitPos = { 680, 500 };
	const Vector2 kEnemyScoreInitPos = kCoinScoreInitPos + kTextShiftOffset;
	const Vector2 kBlockScoreInitPos = kEnemyScoreInitPos + kTextShiftOffset;
}

void SceneGameClear::NormalUpdate()
{
	Input& input = Input::GetInstance();

	--m_coinScoreText->pos.x;

	m_camera->Update();
	m_back->Update();
	m_buttonSystem->Update();
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
	// ���ɂ��炵�Č���銴��
	--m_coinScoreText->pos.x;
	//if (m_coinScoreText->pos.x > )
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

SceneGameClear::~SceneGameClear()
{
	RemoveFontResourceExA("", FR_PRIVATE, NULL);
}

void SceneGameClear::Init()
{
	m_back = std::make_shared<ImageObject>(*m_camera, Vector2::Zero(), kImagePath);
	m_clearText = std::make_shared<ImageObject>(*m_camera, kClearTextPos, kTextPath);

	// �{�^���̐ݒ�
	m_buttonSystem = std::make_shared<ButtonSystem>();
	std::shared_ptr<ButtonReturnToTitle> button = std::make_shared<ButtonReturnToTitle>(Vector2(0,0));
	m_buttonSystem->AddButton(button);
	m_buttonSystem->SetButtonFocus(button);

	AddFontResourceExA(kFontPath.c_str(), FR_PRIVATE, NULL);

	// �����̐ݒ�
	int font = CreateFontToHandle(kFontName.c_str(), kFontSize, kFontThick);
	assert(font != -1 && "�t�H���g�̓ǂݍ��݂Ɏ��s");

	m_coinScoreText = std::make_shared<Text>(kCoinScoreInitPos, kCoinText, font);
	// �萔�ł͎擾�ł��Ȃ��̂ŁAInit�Ō��߂�
	m_coinTextWidth = GetDrawStringWidthToHandle(kCoinText.c_str(), kCoinText.length(), m_coinScoreText->fontHandle);
}

void SceneGameClear::Draw() const
{
	m_back->Draw();
	m_clearText->Draw();
	m_buttonSystem->Draw();

	DrawFormatStringToHandle(static_cast<int>(m_coinScoreText->pos.x), static_cast<int>(m_coinScoreText->pos.y), 0xffffff, m_coinScoreText->fontHandle, m_coinScoreText->text.c_str(), Statistics::GetInstance().ScoreCoin());
	//DrawFormatStringToHandle(static_cast<int>(m_coinScoreText->pos.x), static_cast<int>(m_coinScoreText->pos.y), 0xffffff, m_coinScoreText->fontHandle, "%d", Statistics::GetInstance().ScoreEnemy());
	//DrawFormatStringToHandle(static_cast<int>(m_coinScoreText->pos.x), static_cast<int>(m_coinScoreText->pos.y), 0xffffff, m_coinScoreText->fontHandle, "%d", Statistics::GetInstance().ScoreBlock());
	m_fade.Draw();
}

void SceneGameClear::Entry()
{
	m_fade.Fade(60, 0);
}
