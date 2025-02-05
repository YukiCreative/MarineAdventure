#include "Camera.h"
#include "CircleCollider.h"
#include "Image.h"
#include "Player.h"
#include "SeaUrchin.h"
#include <string>

namespace
{
	const std::string kImageFile = "uni_murasaki_close.png";
	constexpr int kRotateSpeed = 1;
}

SeaUrchin::SeaUrchin(ObjectsController& cont, const Vector2& initPos, Camera& camera, Player& player, const Vector2Int& mapPos) :
	Enemy(cont, player, camera, initPos, mapPos)
{
	m_image = std::make_shared<Image>(kImageFile);
}

void SeaUrchin::Update()
{
	// �v���C���[�Ƃ̓����蔻��
	CollisionStatus collision = m_col->CheckHit(m_playerRef.GetCollider());
	if (collision.isCollide)
	{
		// �v���C���[�Ƀ_���[�W!!!
		m_playerRef.OnDamage();
		m_playerRef.AddForce(collision.overlap);
	}

	// �摜����]
	m_image->RotateGraph(kRotateSpeed);
}

void SeaUrchin::Draw() const
{
	Vector2 drawPos = m_camera.Capture(m_pos);
	m_image->Draw(drawPos);
}
