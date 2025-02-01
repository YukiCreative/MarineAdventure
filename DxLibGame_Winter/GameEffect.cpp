#include "GameEffect.h"
#include "Animation.h"
#include "Camera.h"
#include "SceneController.h"
#include "Scene.h"

GameEffect::GameEffect(const std::string& filename, const Vector2Int& oneImageSize, const int& playSpeed, const Vector2& initPos, const Vector2& offset) :
	GameObject(initPos),
	m_isLoop(false),
	m_offset(),
	m_exRate(1.0f),
	m_reverseX(false)
{
	m_animation = std::make_shared<Animation>();
	m_animation->Init(filename, oneImageSize, playSpeed);
	m_camera = SceneController::GetInstance().CurrentScene()->GetCamera();
}

void GameEffect::Update()
{
	// ’Ç”ö‚·‚é
	if (!m_followGameObject.expired())
	{
		m_pos = m_followGameObject.lock()->GetPos();
	}
	m_animation->Update();

	if (m_isLoop) return;
	if (m_animation->LoopCount())
	{
		m_isDeleted = true;
	}
}

void GameEffect::Draw() const
{
	// ’·‚¢‚È‚ 
	Vector2 drawPos = m_camera.lock()->Capture(m_pos + m_offset);
	m_animation->Draw(drawPos);
}

void GameEffect::SetExRate(const float value)
{
	m_animation->SetExRate(value);
}

void GameEffect::ReverceX(const bool value)
{
	m_animation->ReverceX(value);
}