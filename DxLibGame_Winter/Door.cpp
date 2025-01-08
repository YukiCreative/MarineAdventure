#include "Door.h"
#include "Input.h"
#include "TestScene.h"
#include "SceneController.h"
#include <cassert>

Door::PathMap_t Door::s_paths =
{
	{MapKind::kFish, "Data/MapData/TestMapData32x16.fmf"},
	{MapKind::kPipe, "Data/MapData/TestMapGroundStage.fmf"}
};

void Door::In()
{
	// �Q�[���V�[���Ɏw�����o��
	std::shared_ptr<TestScene> gameScene = std::dynamic_pointer_cast<TestScene>(SceneController::GetInstance().CurrentScene());
	assert(gameScene && "�_�E���L���X�g�Ɏ��s");
	//gameScene->ChangeMap();
}

void Door::SetNextMap(int mapPartsNum)
{

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
