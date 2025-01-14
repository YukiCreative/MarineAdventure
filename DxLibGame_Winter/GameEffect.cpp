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
	// �ǔ�����
	if (!m_followGameObject.expired())
	{
		m_pos = m_followGameObject.lock()->GetPos();
	}
	m_animation->Update();
}

void GameEffect::Draw() const
{
	// �J�������Ȃ�
	m_animation->Draw();
}