#include "GameEffect.h"
#include "Animation.h"

GameEffect::GameEffect(const std::shared_ptr<Animation>& animInstance, const Vector2& initPos, const Vector2& offset = Vector2::Zero()) :
	GameObject(initPos),
	m_isLoop(false),
	m_animation(animInstance)
{
}

GameEffect::GameEffect(const std::string& filename, const Vector2Int& oneImageSize, const int& playSpeed, const Vector2& initPos, const Vector2& offset = Vector2::Zero()) :
	GameObject(initPos),
	m_isLoop(false)
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
	// ƒJƒƒ‰‚ª‚È‚¢
	m_animation->Draw();
}