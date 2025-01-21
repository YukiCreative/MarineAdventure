#include "GameEffect.h"
#include "Animation.h"
#include "Camera.h"
#include "SceneController.h"
#include "Scene.h"

GameEffect::GameEffect(const std::string& filename, const Vector2Int& oneImageSize, const int& playSpeed, const Vector2& initPos, const Vector2& offset) :
	GameObject(initPos),
	m_isLoop(false),
	m_offset()
{
	m_animation = std::make_shared<Animation>();
	m_animation->Init(filename, oneImageSize, playSpeed);
}

void GameEffect::Update()
{
	// ’Ç”ö‚·‚é
	if (!m_followGameObject.expired())
	{
		m_pos = m_followGameObject.lock()->GetPos();
	}
	m_animation->Update();
}

void GameEffect::Draw() const
{
	// ’·‚¢‚È‚ 
	std::weak_ptr<Camera> camera = SceneController::GetInstance().CurrentScene()->GetCamera();
	Vector2 drawPos = camera.lock()->Capture(m_pos + m_offset);
	m_animation->Draw(drawPos);
}