#include "HPUI.h"
#include "Animation.h"
#include <string>

namespace
{
	const std::string kFullHertIdleFile = "HeartIdle.png";
	const std::string kHeartDamageFile  = "HeartDamage.png";
	const std::string kEmptyHeartFile   = "HeartEmpty.png";
	constexpr     int kOneImageSize     = 32;
	constexpr     int kPlaySpeed        =  3;
	constexpr     int kNormalPlaySpeed  = 20;
	constexpr   float kHeartExRate      = 1.5f;

	const  Vector2 kHeartShiftingOffset = { 80, 0 };
	const  Vector2 kDrawBoxSize         = { 500, 50 };
}

void HitPointHeart::Normal()
{
	// �A�j���[�V������������
	m_nowAnim->Update();
}

void HitPointHeart::Damage()
{
	m_nowAnim->Update();
	// ��莞�Ԃ�������Empty��
	if (m_nowAnim->LoopCount() < 3) return;

	m_nowAnim->ResetLoopCount();
	m_state = &HitPointHeart::Normal;
	m_nowAnim = m_emptyAnim;
}

HitPointHeart::HitPointHeart(const Vector2& initPos) :
	GameObject(initPos),
	m_state(&HitPointHeart::Normal),
	m_isFull(true)
{
	m_emptyAnim  = std::make_shared<Animation>();
	m_fullAnim   = std::make_shared<Animation>();
	m_damageAnim = std::make_shared<Animation>();

	m_emptyAnim ->Init(kEmptyHeartFile,   kOneImageSize, kPlaySpeed);
	m_fullAnim  ->Init(kFullHertIdleFile, kOneImageSize, kNormalPlaySpeed);
	m_damageAnim->Init(kHeartDamageFile,  kOneImageSize, kPlaySpeed);

	m_emptyAnim->SetExRate(kHeartExRate);
	m_fullAnim->SetExRate(kHeartExRate);
	m_damageAnim->SetExRate(kHeartExRate);

	m_nowAnim = m_fullAnim;
}

void HitPointHeart::Update()
{
	(this->*m_state)();
}

void HitPointHeart::Draw() const
{
	// UI�Ȃ̂ŃJ�����͂���Ȃ�����
	m_nowAnim->Draw(m_pos);
}

void HitPointHeart::OnDamage()
{
	// ��ԑJ��
	m_nowAnim = m_damageAnim;
	m_isFull = false;
	m_state = &HitPointHeart::Damage;
}

void HitPointHeart::OnRecovery()
{
	m_nowAnim->ResetLoopCount();
	m_nowAnim = m_fullAnim;
	m_state = &HitPointHeart::Normal;
	m_isFull = true;
}

// ============================================

HitPoints::HitPoints(const Vector2& initPos) :
	GameObject(initPos)
{
	Vector2 pos = m_pos + kHeartShiftingOffset;
	// �z��̏�����
	for (auto& haert : m_hearts)
	{
		// �E���獶�ɋl�߂Ă���
		haert = std::make_shared<HitPointHeart>(pos);
		pos += kHeartShiftingOffset;
	}
}

void HitPoints::Update()
{
	for (auto& heart : m_hearts)
	{
		heart->Update();
	}
}

void HitPoints::Draw() const
{
	// ���̘g
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
	DrawBox(static_cast<int>(m_pos.x), static_cast<int>(m_pos.y - kDrawBoxSize.y),
		static_cast<int>(m_pos.x + kDrawBoxSize.x), static_cast<int>(m_pos.y + kDrawBoxSize.y),
		0xffffff, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	for (const auto& heart : m_hearts)
	{
		heart->Draw();
	}
}

void HitPoints::OnDamage(const int damageAmount)
{
	int damage = damageAmount;
	// ���Ɍ��Ă���
	for (auto& heart : m_hearts)
	{
		if (!heart->IsFull()) continue;

		heart->OnDamage();
		--damage;
		// �������炷�̗͂������Ȃ珈�������Ȃ�
		if (damage == 0) return;
	}
}

void HitPoints::OnRecovery(const int recoverAmount)
{
	int damage = recoverAmount;
	// *�t��*�Ɍ��Ă���
	for (auto i = m_hearts.rbegin(); i != m_hearts.rend(); ++i)
	{
		// ����
		if ((*i)->IsFull()) continue;

		(*i)->OnRecovery();
		--damage;
		// �������₷�̗͂������Ȃ珈�������Ȃ�
		if (damage == 0) return;
	}
}
