#include "Door.h"
#include "Input.h"
#include "SceneGame.h"
#include "SceneController.h"
#include <cassert>
#include "Image.h"
#include "Camera.h"
#include "CircleCollider.h"
#include "Player.h"

namespace
{
	const std::string kImagePath = "OpenedDoor.png";
	// 8~のオブジェクト番号を持っているドアを、0～のIdに変える
	constexpr int kIdOffset = 8;
	constexpr float kImageExRate = 80.0f / 32.0f;

	constexpr float kDoorColRadius = 30.0f;
	const Vector2 kDoorAppearanceOffset(0, -32);
}

bool Door::CheckInDoor() const
{
	if (!Input::GetInstance().IsTrigger("Attack")) return false;

	// プレイヤーとの当たり判定を取る
	CollisionStatus collision = m_collider->CheckHit(m_player.GetCollider());
	if (!collision.isCollide) return false;

	// ボタンが押されていて、かつプレイヤーが接触していたらtrue
	return true;
}

Door::Door(Player& player, Camera& camera, const Vector2& initPos, const std::string& path, const Vector2& nextPlayerPos) :
	GameObject(initPos),
	m_camera(camera),
	m_player(player),
	m_path(path),
	m_nextPlayerPos(nextPlayerPos)
{
	m_image    = std::make_shared<Image>         (kImagePath);
	m_collider = std::make_shared<CircleCollider>(m_pos, kDoorColRadius);

	m_image->SetExRate(kImageExRate);
	m_image->SetOffset(kDoorAppearanceOffset);
}

void Door::Update()
{
	Input& input = Input::GetInstance();
	Vector2 axis = input.GetInputAxis();

	// ドアに入る処理

	if (CheckInDoor())
	{
		In();
	}
}

void Door::Draw() const
{
	Vector2 drawPos = m_camera.Capture(m_pos);
	m_image->Draw(drawPos);

#if _DEBUG
	m_collider->DrawColliderRange_Debug(m_camera.DrawOffset());
#endif
}
