#include "Boss.h"
#include "Animation.h"
#include "CircleCollider.h"
#include "Camera.h"
#include "Physics.h"

namespace
{
	const Vector2Int kAnimationImageSize(32, 32);
	const HitPoint kMaxHitPoint(5);
	const std::string kBossIdleAnimPass = "Idle (32x32).png";
}

void Boss::Idle()
{
}

void Boss::Damage()
{
}

void Boss::Death()
{
}

Boss::Boss(Player& player, Camera& camera, Vector2 initPos) :
	Enemy(player, camera, initPos),
	m_stateFrameCount(0),
	m_state(&Boss::Idle)
{
	m_anim = std::make_shared<Animation>();
	m_anim->Init(kBossIdleAnimPass, kAnimationImageSize, 1);
	m_physics = std::make_shared<Physics>(10.0f, 10.0f);
	m_col = std::make_shared<CircleCollider>(m_pos, 50.0f);

	m_hp = kMaxHitPoint;
}

void Boss::Update()
{
	m_pos += m_physics->Update();
	(this->*m_state)();
}

void Boss::Draw() const
{
	Vector2 drawPos = m_camera.Capture(m_pos);
	m_anim->Draw(drawPos);
}