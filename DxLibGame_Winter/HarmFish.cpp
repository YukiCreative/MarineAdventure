#include "HarmFish.h"
#include <DxLib.h>
#include "Camera.h"
#include <memory>
#include "Physics.h"

namespace
{
	constexpr int kRadius = 20;
}

void HarmFish::Idle()
{
	// �ҋ@���[�V�������s
	// Player�Ƃ̐ڐG���������
	//if ()
	// �U����Ԃ̃v���C���[�ɐG�ꂽ��Damage
}

void HarmFish::Damage()
{
	// hp���炷
	// 0�ɂȂ�����Death
}

void HarmFish::Death()
{
	// ������
	// Enemy���Ǘ����Ă�N���X�ɖ₢���킹�ď����Ă��炤�����ɂ��悤����
}

HarmFish::HarmFish(Camera& camera) :
	Enemy(camera),
	m_state(&HarmFish::Idle)
{
	// ���Ă��ɂȂ邯�Ǒ��v����
	m_physics = std::make_shared<Physics>(1.0f, 1.0f);
	m_physics->UseConstantForce(false);
}

void HarmFish::Update()
{
	// ��Ԃɉ�����������
	(this->*m_state)();

	m_pos += m_physics->Update();
}

void HarmFish::Draw()
{
	Vector2 screenPos = m_camera.Capture(m_pos);
	DrawCircle(static_cast<int>(screenPos.x), static_cast<int>(screenPos.y), kRadius, 0x0000ff);
}