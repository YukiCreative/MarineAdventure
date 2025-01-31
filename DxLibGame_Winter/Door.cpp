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

	// 座標
	//                                    ↓PlatinumのX  ↓〃Y
	const Vector2 kStage1ToStage2 = { 80 * (2 - 8), 80 * (8 - 5) };
	const Vector2 kStage2ToStage3 = { 80 * (2 - 8), 80 * (5- 5) };
}

Door::PathMap_t Door::s_paths =
{
	{MapKind::kStage2, "Data/MapData/Stage2.fmf"},
	{MapKind::kStage3, "Data/MapData/Stage3.fmf"}
};

Door::DoorMap_t Door::s_doors =
{
	{DoorKind::kStage1ToStage2, DoorStatus(Door::s_paths[MapKind::kStage2], kStage1ToStage2)},
	{DoorKind::kStage2ToStage3, DoorStatus(Door::s_paths[MapKind::kStage3], kStage2ToStage3)}
};

bool Door::CheckInDoor()
{
	if (!Input::GetInstance().IsTrigger("Attack")) return false;

	// プレイヤーとの当たり判定を取ってます
	CollisionStatus collision = m_collider->CheckHit(m_player.GetCollider());
	if (!collision.isCollide) return false;

	// つまり　ボタンが押されていて、かつプレイヤーが接触していたらtrue
	return true;
}

void Door::In() const
{
	// ゲームシーンに指示を出す
	std::shared_ptr<SceneGame> gameScene = std::dynamic_pointer_cast<SceneGame>(SceneController::GetInstance().CurrentScene());
	assert(gameScene && "ダウンキャストに失敗");
	DoorStatus mystatus = s_doors[m_myKind];
	gameScene->ChangeMapWithFadeOut(mystatus.path, mystatus.appearPos);
}

Door::Door(Player& player, Camera& camera, const Vector2& initPos, const int& mapPartsNum) :
	GameObject(initPos),
	m_camera(camera),
	m_player(player)
{
	m_myKind = static_cast<DoorKind>(mapPartsNum - kIdOffset);

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
