#include "Coin.h"
#include "Camera.h"
#include "Player.h"
#include "Animation.h"

namespace
{
	const std::string  kFile = "SmallCoin.png";
	const Vector2Int   kSize = { 16, 16 };
	constexpr int kPlaySpeed = 5;
	constexpr int kGetThreshold;
}

SmallCoin::SmallCoin(Player& player, Camera& camera, const Vector2& initPos) :
	GameObject(initPos),
	m_player(player),
	m_camera(camera)
{
	m_anim = std::make_shared<Animation>();
	m_anim->Init(kFile, kSize, kPlaySpeed);
}

void SmallCoin::Update()
{
	m_anim->Update();

	Vector2 rerativeToPlayer = m_pos - m_player.GetPos();
	// ƒvƒŒƒCƒ„[‚ª‹ß‚Ã‚¢‚½‚çŽæ“¾‚Å‚«‚é
	if (rerativeToPlayer.SqrMagnitude() )
}

void SmallCoin::Draw() const
{
	Vector2 drawPos = m_camera.Capture(m_pos);
	m_anim->Draw(drawPos);
}
