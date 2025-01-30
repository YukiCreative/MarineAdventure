#include "Coin.h"
#include "Camera.h"
#include "Player.h"
#include "Animation.h"
#include "SceneController.h"

namespace
{
	const std::string  kFile = "SmallCoin.png";
	const Vector2Int   kSize = { 16, 16 };
	constexpr int kPlaySpeed = 5;
	constexpr int kGetThreshold = 1000;
}

SmallCoin::SmallCoin(Player& player, Camera& camera, const Vector2& initPos) :
	GameObject(initPos),
	m_player(player),
	m_camera(camera)
{
	m_anim = std::make_shared<Animation>();
	m_anim->Init(kFile, kSize, kPlaySpeed);

	// キャッシュすとこ
	m_scene = SceneController::GetInstance().CurrentScene();
}

void SmallCoin::Update()
{
	m_anim->Update();

	Vector2 rerativeToPlayer = m_pos - m_player.GetPos();
	// プレイヤーが近づいたら取得できる
	if (rerativeToPlayer.SqrMagnitude() > kGetThreshold)
	{
	}
}

void SmallCoin::Draw() const
{
	Vector2 drawPos = m_camera.Capture(m_pos);
	m_anim->Draw(drawPos);
}
