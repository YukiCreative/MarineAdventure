#include "Door.h"
#include "Input.h"
#include "TestScene.h"
#include "SceneController.h"
#include <cassert>
#include "Image.h"
#include "Camera.h"
#include "CircleCollider.h"
#include "Player.h"

namespace
{
	const std::string kImagePath = "OpenedDoor.png";
	// 8~�̃I�u�W�F�N�g�ԍ��������Ă���h�A���A0�`��Id�ɕς���
	constexpr int kIdOffset = 8;
	constexpr float kImageExRate = 80.0f / 32.0f;

	constexpr int kDoorColRadius = 30;

	// ����DoorKind�ł܂Ƃ߂��A�z�z��̂ق����������H
	const Vector2 kTutoToMap1(0, 0);
}

Door::PathMap_t Door::s_paths =
{
	{MapKind::kFish, "Data/MapData/TestMapData32x16.fmf"},
	{MapKind::kPipe, "Data/MapData/TestMapGroundStage.fmf"}
};

Door::DoorMap_t Door::s_doors =
{
	{DoorKind::kTutoToMap1, DoorStatus(Door::s_paths[MapKind::kFish], kTutoToMap1)}
};

bool Door::CheckInDoor()
{
	if (Input::GetInstance().IsTrigger("Attack")) return false;

	// �v���C���[�Ƃ̓����蔻�������Ă܂�
	CollisionStatus collision = m_collider->CheckHit(m_player.GetCollider());
	if (!collision.isCollide) return false;

	return true;
}

void Door::In()
{
	// �Q�[���V�[���Ɏw�����o��
	std::shared_ptr<TestScene> gameScene = std::dynamic_pointer_cast<TestScene>(SceneController::GetInstance().CurrentScene());
	assert(gameScene && "�_�E���L���X�g�Ɏ��s");
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
}

void Door::Update()
{
	Input& input = Input::GetInstance();
	Vector2 axis = input.GetInputAxis();

	// �h�A�ɓ��鏈��

	if (CheckInDoor())
	{
		In();
	}
}

void Door::Draw() const
{
	Vector2 drawPos = m_camera.Capture(m_pos);
	m_image->Draw(drawPos);
}
