#include "DoorStageClear.h"
#include "SceneController.h"
#include "SceneGame.h"
#include <cassert>

namespace
{
	// �����N���A��ʂɍs���̂Ń}�b�v�͂ǂ�ł�����
	// �ł��h�A�ɓ������Ƃ����n��Ȃ̂Œn��ɏo��悤�ɂ���
	const std::string kMapPath = "Data/MapData/Stage2";
	const Vector2 kNextPlayerPos = { 80 * (5 - 8), 80 * (35 - 5) };
}

void DoorGameClear::Entry()
{
	// ���̊֐��������
}

void DoorGameClear::In()
{
	// �Q�[���V�[���Ɏw�����o��
	std::shared_ptr<SceneGame> gameScene = std::dynamic_pointer_cast<SceneGame>(SceneController::GetInstance().CurrentScene());
	assert(gameScene && "�_�E���L���X�g�Ɏ��s");

	gameScene->GameClear();
}

DoorGameClear::DoorGameClear(Player& player, Camera& camera, const Vector2& initPos) :
	Door(player, camera, initPos, kMapPath, kNextPlayerPos)
{
}
