#include "Door.h"
#include "Input.h"
#include "TestScene.h"
#include "SceneController.h"
#include <cassert>
#include "Image.h"

namespace
{
	const std::string kImagePath;

	// ����DoorKind�ł܂Ƃ߂��A�z�z��̂ق����������H
	const Vector2 kTutoTpMap1(0, 0);
}

Door::PathMap_t Door::s_paths =
{
	{MapKind::kFish, "Data/MapData/TestMapData32x16.fmf"},
	{MapKind::kPipe, "Data/MapData/TestMapGroundStage.fmf"}
};

Door::DoorMap_t Door::s_doors =
{
	{DoorKind::kTutoToMap1, DoorStatus(Door::s_paths[MapKind::kFish], kTutoTpMap1)}
};

void Door::In()
{
	// �Q�[���V�[���Ɏw�����o��
	std::shared_ptr<TestScene> gameScene = std::dynamic_pointer_cast<TestScene>(SceneController::GetInstance().CurrentScene());
	assert(gameScene && "�_�E���L���X�g�Ɏ��s");
	DoorStatus mystatus = s_doors[m_myKind];
	gameScene->ChangeMap(mystatus.path, mystatus.appearPos);
}

void Door::Init(int mapPartsNum)
{
	m_myKind = static_cast<DoorKind>(mapPartsNum);
	m_image = std::make_shared<Image>("");
}

void Door::Update()
{
	Input& input = Input::GetInstance();
	Vector2 axis = input.GetInputAxis();

	// �h�A�ɓ���̂͂ǂ̑���ɂ��悤
	if (input.IsTrigger("Attack"))
	{
		In();
	}
}

void Door::Draw() const
{

}
