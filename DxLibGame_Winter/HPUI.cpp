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

	const     Vector2 kUIShiftingOffset = { 80, 0 };
}

void HitPointHeart::Normal()
{
	// アニメーション流すだけ
	m_nowAnim->Update();
}

void HitPointHeart::Damage()
{
	m_nowAnim->Update();
	// 一定時間たったらEmptyに
	if (m_nowAnim->LoopCount() < 3) return;

	m_nowAnim->ResetLoopCount();
	m_state = &HitPointHeart::Normal;
	m_nowAnim = m_emptyAnim;
}

HitPointHeart::HitPointHeart(const Vector2& initPos) :
	m_state(&HitPointHeart::Normal),
	m_isFull(true)
{
	m_emptyAnim  = std::make_shared<Animation>();
	m_fullAnim   = std::make_shared<Animation>();
	m_damageAnim = std::make_shared<Animation>();

	m_emptyAnim ->Init(kEmptyHeartFile,   kOneImageSize, kPlaySpeed);
	m_fullAnim  ->Init(kFullHertIdleFile, kOneImageSize, kPlaySpeed);
	m_damageAnim->Init(kHeartDamageFile,  kOneImageSize, kPlaySpeed);
}

void HitPointHeart::Update()
{
	m_nowAnim->Update();
	(this->*m_state)();
}

void HitPointHeart::Draw() const
{
	// UIなのでカメラはいらないかな
	m_nowAnim->Draw(m_pos);
}

void HitPointHeart::OnDamage()
{
	// 状態遷移
	m_nowAnim = m_damageAnim;
	m_isFull = false;
	m_state = &HitPointHeart::Damage;
}

void HitPointHeart::OnRecovery()
{
	m_nowAnim = m_fullAnim;
	m_isFull = true;
}

// ============================================

HitPoints::HitPoints(const Vector2& initPos) :
	GameObject(initPos)
{
	//Vector2
	// 配列の初期化
	for (auto& haert : m_hearts)
	{
		// 右から左に詰めていく
		//haert = std::make_shared<HitPointHeart>();
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
	for (const auto& heart : m_hearts)
	{
		heart->Draw();
	}
}

void HitPoints::OnDamage(const int damageAmount)
{
	int damage = damageAmount;
	// 順に見ていく
	for (auto& heart : m_hearts)
	{
		if (!heart->IsFull()) continue;

		heart->OnDamage();
		--damage;
		// もう減らす体力が無いなら処理をしない
		if (damage == 0) return;
	}
}

void HitPoints::OnRecovery(const int recoverAmount)
{
	int damage = recoverAmount;
	// *逆順*に見ていく
	for (auto i = m_hearts.rbegin(); i == m_hearts.rend(); ++i)
	{
		// きも
		if ((*i)->IsFull()) continue;

		(*i)->OnRecovery();
		--damage;
		// もう増やす体力が無いなら処理をしない
		if (damage == 0) return;
	}
}
