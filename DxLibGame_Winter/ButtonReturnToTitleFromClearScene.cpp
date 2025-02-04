#include "ButtonReturnToTitleFromClearScene.h"
#include "game.h"
#include "Image.h"
#include "SceneController.h"
#include "SceneGameClear.h"
#include <cassert>

namespace
{
	const std::string kFocusedImageFile = "ButtonReturnToTitle_Clear.png";
	const std::string kNoFocusedImageFile = "ButtonReturnToTitle_Clear_NoF.png";

	// ���ꂩ����Ƃ��������̎����ɂȂ��ł�
	constexpr float kCycleFactor = 0.05f;
	constexpr float kBaseButtonExpand = 1.0f;
	constexpr float kPlusExpandPoint = 0.5f;
}

void ButtonReturnToTitleFromClearScene::FocusedUpdate()
{
	++m_frameCount;
	m_image->SetExRate(kBaseButtonExpand + abs(sinf(m_frameCount * kCycleFactor) * kPlusExpandPoint));
}

void ButtonReturnToTitleFromClearScene::NormalUpdate()
{

}

ButtonReturnToTitleFromClearScene::ButtonReturnToTitleFromClearScene(const Vector2& initPos) :
	Button(initPos),
	m_frameCount(0),
	m_transparencyParam(255)
{
	m_image = std::make_shared<Image>(kNoFocusedImageFile);
	m_image->ExpandGraph(kBaseButtonExpand);
	m_image->SetImageBlendMode(DX_BLENDMODE_ALPHA, m_transparencyParam);
}

void ButtonReturnToTitleFromClearScene::OnFocused()
{
	InvertState();
	m_image->SetGraph(kFocusedImageFile);
}

void ButtonReturnToTitleFromClearScene::OnDisfocused()
{
	InvertState();
	m_image->SetGraph(kNoFocusedImageFile);
	m_image->SetExRate(kBaseButtonExpand);
	m_frameCount = 0;
}

void ButtonReturnToTitleFromClearScene::OnPressed()
{
	std::shared_ptr<SceneGameClear> clearScene = std::dynamic_pointer_cast<SceneGameClear>(SceneController::GetInstance().CurrentScene());
	assert(clearScene && "�_�E���L���X�g�Ɏ��s����");
	clearScene->ReturnToTitle();
}

void ButtonReturnToTitleFromClearScene::Draw() const
{
	m_image->Draw(m_pos);
}

void ButtonReturnToTitleFromClearScene::ChangeTransparency(const int param)
{
	m_image->SetImageBlendPal(param);
}
