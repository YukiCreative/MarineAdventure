#include "DoorStageClear.h"
#include "SceneController.h"

namespace
{
	// �����N���A��ʂɍs���̂Ń}�b�v�͂ǂ�ł�����
	// �ł��h�A�ɓ������Ƃ����n��Ȃ̂Œn��ɏo��悤�ɂ���
	const std::string kMapPath = "Data/MapData/Stage2";
	const Vector2 kNextPlayerPos = { 80 * (5 - 8), 80 * (35 - 5) };
}

void DoorGameClear::Entry()
{
	// �����ɃV�[���J��
	SceneController::GetInstance().ChangeScene("Clear");
}

DoorGameClear::DoorGameClear(Player& player, Camera& camera, const Vector2& initPos) :
	Door(player, camera, initPos, kMapPath, kNextPlayerPos)
{
}
