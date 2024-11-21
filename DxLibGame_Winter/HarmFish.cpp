#include "HarmFish.h"
#include <DxLib.h>
#include "Camera.h"
#include <memory>
#include "Physics.h"
#include "Player.h"
#include "CircleCollider.h"
#include "EnemyController.h"

namespace
{
	constexpr int kInitHp = 2;
	constexpr int kRadius = 20;
	constexpr int kDamageMortionFrame = 60;
}

void HarmFish::Idle()
{
	// �ҋ@���[�V�������s
	// Player�Ƃ̐ڐG���������
	if (m_collider->CheckHit(m_playerRef.GetCollider()))
	{
		// ����Player�̏�Ԃ��U����ԂȂ�
		if (m_playerRef.CheckState(PlayerState::kAttack) || m_playerRef.CheckState(PlayerState::kStrongAttack))
		{
			// ������HP�����炷
			--m_hp;
			printf("HP%d�ɂȂ���", m_hp);
			m_graphic = ">_<";
			m_state = &HarmFish::Damage;
			(this->*m_state)();
			return;
		}
		else
		{
			// �����Ńv���C���[�Ƀ_���[�W�������Ă�����
			//m_playerRef.
		}
	}
}

void HarmFish::Damage()
{
	++m_stateFrameCount;
	if (m_hp <= 0)
	{
		m_stateFrameCount = 0;
		printf("����");
		m_graphic = "o_o";
		m_state = &HarmFish::Death;
		return;
	}
	// �A�j���[�V����������
	// 0�ɂȂ�����Death
	if (m_stateFrameCount > kDamageMortionFrame)
	{
		m_stateFrameCount = 0;
		m_graphic = "^_^";
		m_state = &HarmFish::Idle;
		(this->*m_state)();
		return;
	}
}

void HarmFish::Death()
{
	++m_stateFrameCount;
	if (m_stateFrameCount > kDamageMortionFrame)
	{
		// ������
		// Enemy���Ǘ����Ă�N���X�ɖ₢���킹�ď����Ă��炤�����ɂ��悤����
		m_isDead = true;
		return;
	}
}

HarmFish::HarmFish(Player& player, Camera& camera, EnemyController& controller, Vector2 spawnPos) :
	Enemy(player, camera, controller, spawnPos),
	m_state(&HarmFish::Idle),
	m_stateFrameCount(0),
	m_graphic("^_^")
{
	// ���Ă��ɂȂ邯�Ǒ��v����
	m_physics = std::make_shared<Physics>(1.0f, 1.0f);
	m_physics->UseConstantForce(false);
	m_collider = std::make_shared<CircleCollider>(m_pos, kRadius);
	m_hp = kInitHp;
}

void HarmFish::Update()
{
	// ��Ԃɉ�����������
	(this->*m_state)();

	m_pos += m_physics->Update();

	// Update�̌��ʁA��ʊO�ɏo���玀�S
	if (CheckScreenOut())
	{
		m_isDead = true;
	}
}

void HarmFish::Draw()
{
	Vector2 screenPos = m_camera.Capture(m_pos);
	DrawCircle(static_cast<int>(screenPos.x), static_cast<int>(screenPos.y), kRadius, 0x0000ff);
	int width = GetDrawStringWidth(m_graphic.c_str(), m_graphic.size());
	DrawFormatString(static_cast<int>(screenPos.x) - width * 0.5f, static_cast<int>(screenPos.y) - 5, 0xffffff, m_graphic.c_str());
}