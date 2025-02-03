#include "Animation.h"
#include "Camera.h"
#include "GameEffect.h"
#include "ObjectsController.h"
#include "Player.h"
#include "SceneController.h"
#include "SceneGame.h"
#include "SmallCoin.h"
#include "SoundManager.h"
#include "Statistics.h"

namespace
{
	const std::string  kFile = "SmallCoin.png";
	const Vector2Int   kSize = { 16, 16 };
	constexpr int kPlaySpeed = 5;
	constexpr float kExRate = 3.0f;
	const std::string kEffectFile = "CoinEffect.png";
	const Vector2Int kEffectImageSize = { 32, 32 };
	const std::string kGetSound = "コイン獲得音.mp3";

	constexpr int kGetThreshold = 5000;
}

SmallCoin::SmallCoin(Player& player, Camera& camera, const Vector2& initPos, ObjectsController& cont) :
	GameObject(initPos),
	m_player(player),
	m_camera(camera),
	m_cont(cont)
{
	m_anim = std::make_shared<Animation>();
	m_anim->Init(kFile, kSize, kPlaySpeed);
	m_anim->SetExRate(kExRate);
}

void SmallCoin::Update()
{
	m_anim->Update();

	Vector2 rerativeToPlayer = m_pos - m_player.GetPos();
	// プレイヤーが近づいたら取得できる
	if (rerativeToPlayer.SqrMagnitude() < kGetThreshold)
	{
		// エフェクト出す
		auto effect = m_cont.SpawnEffect(kEffectFile, kEffectImageSize, kPlaySpeed, m_pos);
		effect->SetExRate(kExRate);
		m_player.OnRecovery();
		SoundManager::GetInstance().Play(kGetSound);
		m_isDeleted = true;
		Statistics::GetInstance().GotCoin();
	}
}

void SmallCoin::Draw() const
{
	Vector2 drawPos = m_camera.Capture(m_pos);
	m_anim->Draw(drawPos);
}
