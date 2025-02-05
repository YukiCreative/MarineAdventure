#include "Camera.h"
#include "CircleCollider.h"
#include "Image.h"
#include "Player.h"
#include "SeaUrchin.h"
#include "Physics.h"
#include <string>

namespace
{
	const std::string kImageFile = "uni_murasaki_close.png";
	constexpr float kRotateSpeed = 0.5f;
	constexpr float kColRadius = 30;
	// 押されてもテコでも動かない
	constexpr float kWeight = 9999;
	constexpr float kVolume = 1;
}

SeaUrchin::SeaUrchin(ObjectsController& cont, const Vector2& initPos, Camera& camera, Player& player, const Vector2Int& mapPos) :
	Enemy(cont, player, camera, initPos, mapPos)
{
	m_col = std::make_shared<CircleCollider>(m_pos, kColRadius);
	m_image = std::make_shared<Image>(kImageFile);
	m_image->SetExRate(0.2f);

	m_physics = std::make_shared<Physics>(kWeight, kVolume);
}

void SeaUrchin::Update()
{
	// プレイヤーとの当たり判定
	CollisionStatus collision = m_col->CheckHit(m_playerRef.GetCollider());
	if (collision.isCollide)
	{
		// プレイヤーにダメージ!!!
		m_playerRef.OnDamage();
		m_playerRef.AddForce(-collision.overlap);
	}

	// 画像を回転
	m_image->RotateGraph(kRotateSpeed);
}

void SeaUrchin::Draw() const
{
	Vector2 drawPos = m_camera.Capture(m_pos);
	m_image->Draw(drawPos);
}
