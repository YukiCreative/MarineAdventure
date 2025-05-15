#include "ButtonReturnToTitle.h"
#include "Image.h"
#include "ScenePause.h"
#include "SceneController.h"
#include <cassert>

namespace
{
	const std::string kImagePath          = "ButtonReturnToTitle.png";
	const std::string kImagePassNoFocused = "ButtonReturnToTitle_NoFocused.png";

	// これかけるといい感じの周期になるんです
	constexpr float kCycleFactor = 0.05f;
	constexpr float kBaseButtonExpand = 1.0f;
	constexpr float kPlusExpandPoint = 0.5f;
}

void ButtonReturnToTitle::FocusedUpdate()
{
	++m_frameCount;
	m_image->SetExRate(kBaseButtonExpand + abs(sinf(m_frameCount * kCycleFactor) * kPlusExpandPoint));
}

void ButtonReturnToTitle::NormalUpdate()
{
}

ButtonReturnToTitle::ButtonReturnToTitle(Vector2 initPos) :
	Button(initPos),
	m_frameCount(0)
{
	m_image = std::make_shared<Image>(kImagePassNoFocused);
	m_image->ExpandGraph(kBaseButtonExpand);
}

ButtonReturnToTitle::~ButtonReturnToTitle()
{
}

void ButtonReturnToTitle::OnFocused()
{
	InvertState();
	m_image->SetGraph(kImagePath);
}

void ButtonReturnToTitle::OnDisfocused()
{
	InvertState();
	m_image->SetGraph(kImagePassNoFocused);
	m_image->SetExRate(kBaseButtonExpand);
	m_frameCount = 0;
}

void ButtonReturnToTitle::OnPressed()
{
	std::shared_ptr<ScenePause> pause = std::dynamic_pointer_cast<ScenePause>(SceneController::GetInstance().CurrentScene());
	assert(pause && "ダウンキャストに失敗した");
	pause->ReturnToTitle();
}

void ButtonReturnToTitle::Draw() const
{
	m_image->Draw(m_pos);
}
